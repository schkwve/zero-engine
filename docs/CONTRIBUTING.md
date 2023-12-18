# Contributing Guide

- Contributing to Zerø Engine is fairly easy. This document shows you how to get started

## General
- The [Codebase Structure](./CODEBASE_STRUCTURE.md) has detailed information about how the various files in this project are structured
- Please ensure that any changes you make are in accordance with the [Coding Guidelines](./CODING_GUIDELINES.md) of this repo

## Submitting changes

- Fork the repo
  - <https://github.com/schkwve/zero-engine/fork>
- Check out a new branch based and name it to what you intend to do:
  - Example:
    ````
    $ git checkout -b BRANCH_NAME
    ````
  - Use one branch per fix / feature
- Commit your changes
  - Please provide a git message that clearly explains what you've done
  - Commit to the forked repository
  - Example:
    ````
    $ git commit -am 'Add a cool feature'
    ````
- Push to the branch
  - Example:
    ````
    $ git push origin BRANCH_NAME
    ````
- Make a pull request
  - Make sure you send the PR to the <code>fooBar</code> branch

If you follow these instructions, your PR will land pretty safely in the main repo!
