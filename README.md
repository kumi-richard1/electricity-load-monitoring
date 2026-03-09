# Electrical Load Monitoring & Billing System

A simple C++ console project for monitoring household electrical appliances, estimating daily energy consumption, and calculating electricity bills.

## Features

- Register appliances
- View all registered appliances
- Search for an appliance by name
- Show daily energy summary
- Calculate electricity bill
- Save appliance records to a file
- Load saved appliance records when the program starts
- Export billing summary to a text file

## Files

- `main.cpp` — main source code
- `appliances.txt` — stores registered appliances
- `billing_summary.txt` — stores generated billing summary

## How It Works

Each appliance has:

- Name
- Power rating in watts
- Number of hours used per day

The program calculates energy usage using:

```text
Energy (kWh/day) = Power (W) × Hours used per day / 1000
```

The total bill is calculated using:

```text
Bill = Total Energy × Cost per kWh
```

## Menu Options

1. Register appliance
2. View appliances
3. Search appliance
4. Energy summary
5. Calculate electricity bill
6. Exit

## How to Compile

Use any C++ compiler such as `g++`.

```bash
g++ main.cpp -o loadmonitor
```

## How to Run

```bash
./loadmonitor
```

On Windows:

```bash
loadmonitor.exe
```

## Example Appliance Record Format

The `appliances.txt` file stores data like this:

```text
Fan,75,8
Television,120,5
Fridge,150,24
```

## Project Build-Up

This project was built in 10 parts:

1. Basic menu shell
2. Appliance structure and registration
3. View appliances
4. Search appliance
5. Energy summary
6. Electricity bill calculation
7. Save appliances to file
8. Load appliances from file
9. Export billing summary
10. Full complete project

## Requirements

- C++ compiler
- Basic terminal or command prompt

## Author

Richard kumi larbi
