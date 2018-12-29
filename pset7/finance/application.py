import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initialize variables
    all_index_info = []
    cash = float(db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"])
    grand_total = cash
    stocks = db.execute("SELECT * FROM purchases WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])

    for stock in stocks:

        # Calculate number of shares purchased
        shares_purchased = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = :user_id AND symbol = :symbol",
                                      user_id=session["user_id"],
                                      symbol=stock["symbol"])

        # Calculate number of shares sold
        shares_sold = db.execute("SELECT SUM(shares) FROM sales WHERE user_id = :user_id AND symbol = :symbol",
                                 user_id=session["user_id"],
                                 symbol=stock["symbol"])

        # Subtract shares sold from shares purchased
        if not shares_sold[0]["SUM(shares)"]:
            shares_sold[0]["SUM(shares)"] = 0
        shares = shares_purchased[0]["SUM(shares)"] - shares_sold[0]["SUM(shares)"]

        # Only continue if at least one share currently owned
        if shares > 0:

            # Retrive key stock details
            symbol_lookup = lookup(stock["symbol"])

            # Calculate price + total value
            price = symbol_lookup["price"]
            total_value = price * shares
            grand_total += total_value

            all_index_info.append({
                "symbol": stock["symbol"],
                "name": symbol_lookup["name"],
                "shares": shares,
                "price": usd(price),
                "total_value": usd(total_value)
            })

    return render_template("index.html",
                           cash=usd(cash),
                           all_index_info=all_index_info,
                           grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialize key variables
        symbol = request.form.get("symbol")
        symbol_lookup = lookup(symbol)

        # Try to initialize shares as int
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares can only take integer value")

        # Error check for incorrect symbol input
        if symbol_lookup == None or len(symbol) == 0:
            return apology("invalid symbol")

        # Initialize remaining variables
        price = symbol_lookup["price"]
        user_cash_list = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        user_cash = user_cash_list[0]["cash"]

        # Render apology if the input is blank
        if len(symbol) == 0:
            return apology("symbol can't be blank")

        # Render apology if symbol does not exist
        if not symbol_lookup:
            return apology("symbol doesn't exist")

        # Render apology if shares input is not positive integer
        if shares <= 0:
            return apology("shares must be a positive integer")

        # Render apology – without completing a purchase – if the user cannot afford the number of shares at the current price
        if (price * shares) > user_cash:
            return apology("you can't afford {} shares at the current price" .format(shares), 403)

        # Create db entry for purchase if successful
        db.execute("INSERT INTO purchases (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=symbol,
                   shares=shares,
                   price=price)

        # Update cash for user
        new_cash = user_cash - (price * shares)
        db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id",
                   new_cash=new_cash,
                   user_id=session["user_id"])

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Initialize transations list
    transactions = []

    # Retrieve all purchases
    purchases = db.execute("SELECT * FROM purchases WHERE user_id = :user_id",
                           user_id=session["user_id"])

    # Retrieve all sales
    sales = db.execute("SELECT * FROM sales WHERE user_id = :user_id",
                       user_id=session["user_id"])

    # Iterate through purchases and add to transations
    for purchase in purchases:
        transactions.append({
            "symbol": purchase["symbol"],
            "shares": purchase["shares"],
            "price": usd(purchase["price"] / purchase["shares"]),
            "date": purchase["date"]
        })

    # Iterate through sales and add to transations
    for sale in sales:
        transactions.append({
            "symbol": sale["symbol"],
            "shares": -(sale["shares"]),
            "price": usd(sale["price"] / sale["shares"]),
            "date": sale["date"]
        })

    # Sort transactions in new list
    sorted_transactions = sorted(transactions, key=lambda k: k['date'], reverse=True)

    # Render history page
    return render_template("history.html", sorted_transactions=sorted_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialize key variables
        symbol = request.form.get("symbol")
        symbol_lookup = lookup(symbol)

        # Error check for incorrect symbol input
        if symbol_lookup == None or len(symbol) == 0:
            return apology("invalid symbol")

        return render_template("quoted.html", symbol=symbol, price_usd=usd(symbol_lookup["price"]))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialize user input
        username = request.form.get("username")
        user_password = request.form.get("password")
        user_confirmation = request.form.get("confirmation")

        # Render an apology if the user’s input is blank
        if not username:
            return apology("must enter username")

        # Render an apology if the username already exists
        existing_users = db.execute("SELECT * FROM users WHERE username = :username", username=username)
        if len(existing_users) != 0:
            return apology("username already exists")

        # Render apology if passwords don't match
        if user_password != user_confirmation:
            return apology("passwords do not match")

        # Render apology if either password is blank
        if len(user_password) == 0 or len(user_confirmation) == 0:
            return apology("password can't be blank")

        # Render apology if password is less than six characters
        if len(user_password) < 6:
            return apology("password must be at least 6 characters")

        # Insert new user into users
        db.execute("INSERT INTO users (username, hash) VALUES(:u, :h)",
                   u=username,
                   h=generate_password_hash(user_password, method='pbkdf2:sha256', salt_length=8))

        # Redirect user to login form
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialize key variables
        symbol = request.form.get("symbol")
        shares_requested = int(request.form.get("shares"))
        price = shares_requested * lookup(symbol)["price"]
        user_cash_list = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        user_cash = user_cash_list[0]["cash"]

        # Calculate number of given stock previously purchased
        shares_purchased = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = :user_id AND symbol = :symbol",
                                      user_id=session["user_id"],
                                      symbol=symbol)

        # Calculate number of given stock previously sold
        shares_sold = db.execute("SELECT SUM(shares) FROM sales WHERE user_id = :user_id AND symbol = :symbol",
                                 user_id=session["user_id"],
                                 symbol=symbol)

        # Subtract shares sold from shares purchased
        if not shares_sold[0]["SUM(shares)"]:
            shares_sold[0]["SUM(shares)"] = 0
        shares_owned = shares_purchased[0]["SUM(shares)"] - shares_sold[0]["SUM(shares)"]

        # Render an apology if the user fails to select a stock
        if not symbol:
            return apology("no stock selected")

        # Render an apology if the user does not own any shares
        if not shares_owned > 0:
            return apology("you don't own any {}" .format(symbol))

        # Render an apology if the input is not a positive integer
        if not shares_requested > 0:
            return apology("number of shares must be positive")

        # Render an apology if the user does not own that many shares of the stock
        if shares_requested > shares_owned:
            return apology("you don't have that many {} shares to sell" .format(symbol))

        # Create db entry for sale if successful
        db.execute("INSERT INTO sales (user_id, symbol, shares, price) VALUES(:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"],
                   symbol=symbol,
                   shares=shares_requested,
                   price=price)

        # Update cash for user
        new_cash = user_cash + price
        db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id",
                   new_cash=new_cash,
                   user_id=session["user_id"])

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        # Retrieve symbols for stock owned by user
        symbols = db.execute("SELECT symbol FROM purchases WHERE user_id = :user_id GROUP BY symbol",
                             user_id=session["user_id"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
