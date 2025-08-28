# Unreal Firebase Auth testing project

## Showcase

https://github.com/user-attachments/assets/3dc35405-95c0-4808-8348-f96a770a1a8d


## Timeline:
   - 13:45-14:30 - Research<br/>
   - 19:30-22:27 - Implementation
   
## Project Setup
-> Create a new project in firebase console.<br/>
-> Enable authentication with email/password as provider.<br/>
-> Go to project settings and copy web api key.<br/>
->
**FirebaseAuthTest.h** has a variable named **FireBaseAPIKey** there you have to put web api key of your firebase project.

    - Source
      - FirebaseAuthTest
        FirebaseAuthTest.h

-> Run the project and test the authentication.

> **⚠️ Important note:** As the goal was to create MVP for firebase auth, this project does not perform validation checks like email formate, password has capital or special characters etc, currently it expects you to enter proper email and 6 digit password else it will print error on screen debug message.

## How it works
- There are two classes **UFirebaseRegister** and **UFirebaseLogin** which are responsible for registration and login  respectively async nodes exposed to blueprints.
- Both classes have two delegates **Success** and **Error** which will be called on success and failure of the operation respectively.
- Those are basically calling rest api of firebase auth with provided api key and handling the response.
