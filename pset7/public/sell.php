<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a symbol.");
        }
        else
        {
            $price = lookup(strtoupper($_POST["symbol"]))["price"];
            $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["symbol"]))[0]["shares"];
            $price = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $price * $shares, $_SESSION["id"]);
            
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], strtoupper($_POST["symbol"]));
            CS50::query("INSERT INTO history (user_id, transaction, date, symbol, shares, price) VALUES(?, 'Sell', CURRENT_TIMESTAMP, ?, ?, ?)", 
            $_SESSION["id"], strtoupper($_POST["symbol"]), $shares, $price);
            // redirect to portfolio
            redirect("/");
        }
    }

?>
