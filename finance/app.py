import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    if request.method == "GET":

        # stocks = db.execute("SELECT * FROM transactions WHERE user_id = ? AND buy_sell = 'BUY'", session["user_id"])

        stocks = db.execute("SELECT * FROM portfolio WHERE user_id = ?", session["user_id"])

        user = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])

        cash = user[0]["cash"]

        allstocks = {}

        totalvalue = 0

        for index, row in enumerate(stocks):
            key = row["symbol"]
            counter = 0
            price = lookup(key)
            for row in stocks:
                if key == row["symbol"]:
                    counter = counter + row["amount"]
            totalprice = counter * price["price"]
            # usd(price["price"])
            # usd(totalprice)
            totalvalue = totalprice + totalvalue
            allstocks[key] = {'key': key, 'price': price["price"], 'counter': counter, 'total': totalprice}

        # usd(cash)
        # print(allstocks)
        # print(totalvalue)

        return render_template("index.html", allstocks=allstocks, totalvalue=float(totalvalue), cash=float(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Check if symbol is valid
        if lookup(request.form.get("symbol")) == None:
            return apology("Stock symbol Invalid", 400)

        # Check number of stocks
        number = request.form.get("shares")

        stock = lookup(request.form.get("symbol"))

        user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        cash = user[0]["cash"]

        try:
            number = float(number)
        except:
            return apology("Number of Stocks not an Integer", 400)

        cost = number * stock["price"]

        current_cash = user[0]["cash"] - cost

        if number % 1 != 0:
            return apology("Number of Stocks not an Integer", 400)

        if number < 1:
            return apology("Number of Stocks not a positive Integer", 400)

        if cost > cash:
            return apology("Not enough cash")

        now = datetime.now()

        rows = db.execute("SELECT * FROM transactions")

        db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, 'BUY', ?) ",
                   len(rows), stock["symbol"], number, session["user_id"], now, cost)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, session["user_id"])

        portfolio = {}

        portfolio = db.execute("SELECT * FROM portfolio WHERE user_id =  ? AND symbol = ?", session["user_id"], stock["symbol"])

        if not portfolio:
            db.execute("INSERT INTO portfolio VALUES (?, ?, ?)", session["user_id"], stock["symbol"], number)

        else:
            print(portfolio[0]["amount"])
            x = portfolio[0]["amount"]
            number = number + x
            db.execute("UPDATE portfolio SET amount = ? WHERE user_id = ? AND SYMBOL = ? ",
                       number, session["user_id"], stock["symbol"])

        return redirect("/")

    # Get
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM transactions WHERE user_id = ?", session["user_id"])

    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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

        # Check if symbol is valid
        if lookup(request.form.get("symbol")) == None:
            return apology("Quote Invalid", 400)

        else:
            stock = lookup(request.form.get("symbol"))
            stock["price"] = usd(stock["price"])
            print(stock)
            return render_template("quoted.html", stock=stock)

    # Get
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username is not taken
        if len(rows) != 0:
            return apology("username is taken", 400)

        username = request.form.get("username")
        password = request.form.get("password")

        # Insert person in db
        db.execute("INSERT INTO users(username, hash) VALUES(?, ?);", username, generate_password_hash(password))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has registered in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
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

        now = datetime.now()

        symbol = request.form.get("symbol")

        shares = request.form.get("shares")

        portfolio = db.execute("SELECT amount FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)

        if portfolio[0]["amount"] < int(shares):
            return apology("not enough stocks", 400)
        elif float(shares) % 1 != 0:
            return apology("Number of Stocks not an Integer", 400)
        elif float(shares) < 1:
            return apology("Number of Stocks not a positive Integer", 400)
        else:
            amount = portfolio[0]["amount"] - int(shares)

            db.execute("UPDATE portfolio SET amount = ? WHERE user_id = ? AND symbol = ?", amount, session["user_id"], symbol)

            rows = db.execute("SELECT * FROM transactions")

            sellprice = lookup(symbol)

            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

            print(sellprice["price"])

            tcash = cash[0]["cash"] + sellprice["price"]

            db.execute("UPDATE users SET cash = ? WHERE id = ?", tcash, session["user_id"])

            db.execute("INSERT INTO transactions VALUES (?, ?, ?, ?, ?, 'SELL', ?) ", len(
                rows), symbol, shares, session["user_id"], now, sellprice["price"])

        # print(portfolio)

        return redirect("/")

    else:
        portfolio = db.execute("SELECT * FROM portfolio WHERE user_id = ?", session["user_id"])

        print(portfolio)

        return render_template("sell.html", portfolio=portfolio)

