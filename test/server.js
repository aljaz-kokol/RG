const express = require('express');
const cors = require('cors');
const app = express();

app.use(express.json());
app.use(cors());

app.get('/api/random', (req, res, next ) => {
    let numbers = [];
    for (let i = 0; i < 5; i++) {
        numbers.push(Math.random() * (180 + 0) - 0)
    }
    res.status(200).json(numbers);
});

app.listen(3000, () => {
    console.log("Now listening on port 3000");
});