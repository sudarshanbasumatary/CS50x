<table class="table table-striped">
    <thead>
        <tr>
            <td>Transaction</td>
            <td>Date/Time</td>
            <td>Symbol</td>
            <td>Shares</td>
            <td>Price</td>
        </tr>
    </thead>
    <tbody>
        
    <?php foreach($transactions as $trans): ?>
        <tr>
            <td><?= $trans["transaction"] ?></td>
            <td><?= $trans["date"] ?></td>
            <td><?= $trans["symbol"] ?></td>
            <td><?= $trans["shares"] ?></td>
            <td><?= $trans["price"] ?></td>
        </tr>
    <?php endforeach?>
    
    </tbody>
    
</table>