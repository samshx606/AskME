# C++ OOP Project

## Overview

This project demonstrates basic object-oriented programming (OOP) concepts in C++ by managing classes for users, questions, and answers. Each class has attributes and methods to access specific data.

## Classes

### User
Represents a user with:
- `id`: unique ID
- `name`: full name
- `username`: login username
- `password`: login password

**Methods:**
- `get_id()`, `get_name()`, `get_username()`, `get_password()`: Return the user’s information.

### Question
Represents a question from one user to another with:
- `id`: unique question ID
- `from_user`: sender's username
- `to_user`: recipient's username
- `state`: `true` if answered, `false` otherwise
- `text`: question content

**Methods:**
- `get_id()`, `get_from_user()`, `get_to_user()`, `get_state()`, `get_text()`: Return question information.

### Answer
Represents an answer to a question with:
- `id`: unique answer ID
- `question_id`: ID of the related question
- `text`: answer content

**Methods:**
- `get_id()`, `get_question_id()`, `get_text()`: Return answer information.

## Getting Started


### Compilation and Running
1. To compile, include all headers along with the main source file:

    ```bash
    g++ -o main main.cpp User.h Question.h Answer.h
    ```

2. Run the compiled program:

    ```bash
    ./main
    ```
