<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("deposit_form.php", ["title" => "Deposit Funds"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["fund"]))
        {
            apologize("You must provide funds.");
        }
        else if (!is_numeric($_POST["fund"]) || $_POST["fund"] < 0) {
            apologize("You must provide valid fund.");
        }
        else
        {
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["fund"], $_SESSION["id"]);
            CS50::query("INSERT INTO history (user_id, transaction, date, price) VALUES(?, 'Deposit', CURRENT_TIMESTAMP, ?, ?)", 
            $_SESSION["id"], $_POST["fund"]);
            // redirect to portfolio
            redirect("/");
        }
    }

?>
