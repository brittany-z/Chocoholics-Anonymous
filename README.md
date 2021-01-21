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
$ git branch $EB_functionality_being_added
$ git checkout $EB_functionality_being_added
$ git push origin $EB_functionality_being_added
```
After inputting your username and password, you there will be some output to screen, similar to this:
```bash
Total 0 (delta 0), reused 0 (delta 0)
remote:
remote: Create a pull request for 'EB_test_github_merges' on GitHub by visiting:
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
