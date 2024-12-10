# Cortex : a toy limit order book based trading exchange implementation  with REST API

This application is a **REST API** implemented in C++ using the **Crow** framework. It provides functionality to manage a Limit Order Book, allowing users to submit orders via HTTP requests and retrieve information such as the mid price.

---

## Features

1. **Submit a limit order** (`POST /submit_limit_order`):
    - Accepts a buy or sell limit order in JSON format.
    - Executes the order in the limit order book.
    - Returns a confirmation in JSON format.

2. **Submit a market order** (`POST /submit_market_order`):
    - Accepts a buy or sell market order in JSON format.
    - Executes the order in the limit order book.
    - Returns a confirmation in JSON format.

3. **Submit an cancel order** (`POST /submit_cancel_order`):
    - Accepts a cancel order in JSON format.
    - Executes the order in the limit order book.
    - Returns a confirmation in JSON format.

4. **Get Prices** (`GET /prices`):
   - Accepts a price request on a  given ticker.
   - Returns the best bid and ask prices.

---

## Technologies Used

- **C++11**: Main programming language.
- **Crow**: A C++ web framework (https://crowcpp.org/).
- **std::mutex**: Used for thread safety in concurrent order submissions.