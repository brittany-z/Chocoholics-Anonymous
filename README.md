# Chocoholics-Anonymous

## How to contribute

### Setup

Before working on this project, please cd into Chocoholics-Anonymous, and then change your git username and email:
```bash
$ cd Chocoholics-Anonymous
$ git config --global user.name "Your Name"
$ git config --global user.email "youremail@yourdomain.com"
```

### Setting up a branch

In order to start making changes to the code, please create a developement branch, separate from main. 

To do this, follow the instructions below:
```bash
# Branch names should be your initials in uppercase, followed by a very short description of what functionality you are working on
$ git branch $EB_functionality_being_added # creates a branch
$ git checkout $EB_functionality_being_added # switch to new branch
$ git push origin $EB_functionality_being_added # sync new branch with GitHub
```
After inputting your username and password, you there will be some output to screen, similar to this:
```bash
Total 0 (delta 0), reused 0 (delta 0)
remote:
remote: Create a pull request for 'EB_functionality_being_added' on GitHub by visiting:
remote:      https://github.com/redawl/Chocoholics-Anonymous/pull/new/EB_functionality_being_added
remote:
To https://github.com/redawl/Chocoholics-Anonymous.git
 * [new branch]      EB_functionality_being_added -> EB_test_github_merges

```
The important info to look for in this output:
```bash
Create a pull request for 'EB_functionality_being_added' on GitHub by visiting:
remote:      https://github.com/redawl/Chocoholics-Anonymous/pull/new/EB_functionality_being_added
```
This is the link you will want to follow to create what GitHub calls a "pull request", which is just a fancy way to say, "I want to add my new code to the main branch, can you other people who are working on the project, look at my changes and confirm that they are useful?". 

Following this process will allow us to all confirm changes to the project. 

### Making changes to the code

Edit, create and remove files as normal. When you are ready to save some changes you have made, follow these steps:

```bash
$ git add * # tracks all files
$ git commit -m "Nice descriptive message of what has been changed since the last 'save'" # saves changes 
```
And thats it! When you want to sync your local changes with the github remember to 'push' your changes to GitHub using:
```bash
$ git push origin $name_of_branch
```
