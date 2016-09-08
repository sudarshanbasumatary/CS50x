<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["username"]))
            render("apology.php", ["message" => "Username required"]);
        else if(empty($_POST["password"]))
            render("apology.php", ["message" => "Password required"]);
        else if($_POST["password"] != $_POST["confirmation"])
            render("apology.php", ["message" => "Passwords do not match!"]);
        else {
            $rows = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            if ($rows !== 1)
                render("apology.php", ["message" => "User already exists!"]);
            else {
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                redirect("/index.php");
            }
}
    }

?>