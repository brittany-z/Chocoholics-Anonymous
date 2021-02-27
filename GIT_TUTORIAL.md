# Chocoholics-Anonymous

## How to contribute
1. [Setup](#Setup)
    1. [SSH Keys](#SSH-Keys)
2. [Setting up a branch](#Setting-up-a-branch)
3. [Making Changes to the Code](#Making-changes-to-the-code)
5. [Keeping your Branch up to Date](#Keeping-your-Branch-up-to-Date)
4. [Merge Conflicts](#Merge-Conflicts)

### Setup

Before working on this project, please cd into Chocoholics-Anonymous, and then change your git username and email:
```bash
$ cd Chocoholics-Anonymous
$ git config --global user.name "Your Name"
$ git config --global user.email "youremail@yourdomain.com"
```
#### SSH Keys

You may notice that every time you want to interact with the Github, you have to input your username and password, which will get quite annoying. The way to get around this is by using ssh keys. While they are not required, they will save you quite a lot of time. 

To get started, type this into your terminal:
```bash
$ ssh-keygen -t rsa -C "example@pdx.edu"
```
You wil then get this prompt:
```bash
Enter file in which to save the key (/u/elburch/.ssh/id_rsa):
```
Only enter a file name if you know what you're doing, as this will cause you to need to change a bunch of configuration files. Press enter to proceed to the next prompt. 
```bash
Enter passphrase (empty for no passphrase):
```
This prompt is asking if you want to enter a passphrase every time you interact with github. If you leave it blank and press enter, then no passphrase will be required. 

After getting passed the password prompt, you should see output like this:
```bash
The key fingerprint is:
SHA256:upfotpzv1NVe71IfVXnszlXQB4eT13pXkXaXl+dgh/0 elburch@pdx.edu
The key's randomart image is:
+---[RSA 3072]----+
|              o@O|
|              BB^|
|             ..O%|
|             .. E|
|        S   . .+=|
|       . . . . o=|
|      .....   ..+|
|     .o+o     ...|
|     o*=o      ..|
+----[SHA256]-----+
elburch@ruby:~/Desktop/Chocoholics-Anonymous$
```
Success! You have generated your ssh key!
Now, output your public key to the screen by typing:
```bash
$ cat ~/.ssh/id_rsa.pub
```
Copy all the output of that command, then head over to Github. Click on your profile in the top right corner, and go to settings. Click on SSH and GPG keys, and click new ssh key. 

For the title, I suggest using the name of the server that you created the ssh key on, since ssh keys are unique to servers. After that, paste the output from the cat command into the key field. 

SSH keys should now be set up!

Unfortunately if you followed this guide before and already cloned Chocoholics anonymous, you will need to delete the old repository, and clone it again, but this time use the SSH link, instead of the HTTPS link. If you are not asked to input your username and password, then you are good to go!
### Setting up a branch

In order to start making changes to the code, please create a developement branch, separate from main. 

To do this, follow the instructions below:
```bash
# Branch names should be your initials in uppercase, followed by a very short description of what functionality you are working on
$ git branch EB_functionality_being_added # creates a branch
$ git checkout EB_functionality_being_added # switch to new branch
$ git push origin EB_functionality_being_added # sync new branch with GitHub
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
### Keeping your Branch up to Date

If the main branch is updated while you are working on your branch, you must update your current branch to include the new changes. This is usually very simple, but can become more complicated if there were edits to the same files you are working on in the main branch. Best case scenario, updating you branch would go something like this:
```bash
$ git checkout main # Switch current branch to the main branch
$ git pull origin # Pull new changes on the github to your local folder
$git checkout $name_of_branch # Switch back to your branch
$git merge main # Adds the changes from main to your branch
```
After this, a variety of things could happen, but as long as you carefully read the output, it should be fairly obvious what you should do next. If it is not, then google is your friend. 
### Merge Conflicts

I have zero experience with merge conflicts and Github push requests. 

Merge conflicts happen when a branch that isn't up to date with the main branch when it is combined with main. 

Lets just say I hope we don't have to deal with this issue. If we do though, it will be a learning experience for all of us. 
