# Contribution Guidelines

## Coding Style

* Use C11 style with 3 spaces for C-files.
* Use Google++ style with 3 spaces for indentation for C++ files.
* Header Files:
    - In general, every .cpp file should have an associated .hh file. 
    - There are some common exceptions, such as unit tests and small .cpp files containing just a main() function.
    - Correct use of header files can make a huge difference to the readability, size and performance of your code.
    - Header files should be self-contained (compile on their own) and end in .h or .hh. 
    - Non-header files that are meant for inclusion should end in .inc and be used sparingly.
    - All header files should have #define guards to prevent multiple inclusion.
* Define functions inline only when they are small, say, 10 lines or fewer.
* With few exceptions, place code in a namespace. Namespaces should have unique names based on the project name, and possibly its path. 
* Do not use using-directives (e.g., using namespace foo). Do not use inline namespaces.
* Prefer placing nonmember functions in a namespace; use completely global functions rarely. Do not use a class simply to group static members.
* Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
* Avoid virtual method calls in constructors, and avoid initialization that can fail if you can't signal an error.

## Conventional Commit

* Use [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
A specification for adding human and machine readable meaning to commit messages.

* The commit message should be structured as follows:

````
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
````
The commit contains the following structural elements, to communicate  
intent to the consumers of your library:

1. fix: a commit of the type fix patches a bug in your codebase (this correlates with PATCH in Semantic Versioning).
2. feat: a commit of the type feat introduces a new feature to the codebase (this correlates with MINOR in Semantic Versioning).
3. BREAKING CHANGE: a commit that has a footer BREAKING CHANGE:, or appends a ! after the type/scope, introduces a breaking
API change (correlating with MAJOR in Semantic Versioning). A BREAKING CHANGE can be part of commits of any type.
4. types other than fix: and feat: are allowed, for example @commitlint/config-conventional (based on the the Angular convention)
recommends build:, chore:, ci:, docs:, style:, refactor:, perf:, test:, and others.
5. footers other than BREAKING CHANGE: <description> may be provided and follow a convention similar to git trailer format.
Additional types are not mandated by the Conventional Commits specification, and have no implicit effect in Semantic Versioning
(unless they include a BREAKING CHANGE). A scope may be provided to a commit's type, to provide additional contextual information and is contained within parenthesis, e.g., feat(parser): add ability to parse arrays.

### Specification

The key words 'MUST', 'MUST NOT', 'REQUIRED', 'SHALL', 'SHALL NOT', 'SHOULD',  
'SHOULD NOT', 'RECOMMENDED', 'MAY', and 'OPTIONAL' in this document are to be  
interpreted as described in RFC 2119.

1. Commits MUST be prefixed with a type, which consists of a noun, feat, fix, etc.,
followed by the OPTIONAL scope, OPTIONAL !, and REQUIRED terminal colon and space.

2. The type feat MUST be used when a commit adds a new feature to your application or library.
3. The type fix MUST be used when a commit represents a bug fix for your application.
4. A scope MAY be provided after a type. A scope MUST consist of a noun describing a section of the codebase surrounded by parenthesis, e.g., fix(parser):
5. A description MUST immediately follow the colon and space after the type/scope prefix. The description is a short summary of the code changes, e.g., fix: array parsing issue when multiple spaces were contained in string.
6. A longer commit body MAY be provided after the short description, providing additional contextual information about the code changes. The body MUST begin one blank line after the description.
7. A commit body is free-form and MAY consist of any number of newline separated paragraphs.
8. One or more footers MAY be provided one blank line after the body. Each footer MUST consist of a word token, followed by either a :<space> or <space># separator, followed by a string value (this is inspired by the git trailer convention).
9. A footer's token MUST use - in place of whitespace characters, e.g., Acked-by (this helps differentiate the footer section from a multi-paragraph body). An exception is made for BREAKING CHANGE, which MAY also be used as a token.
10. A footer's value MAY contain spaces and newlines, and parsing MUST terminate when the next valid footer token/separator pair is observed.
11. Breaking changes MUST be indicated in the type/scope prefix of a commit, or as an entry in the footer.
12. If included as a footer, a breaking change MUST consist of the uppercase text BREAKING CHANGE, followed by a colon, space, and description, e.g., BREAKING CHANGE: environment variables now take precedence over config files.
13. If included in the type/scope prefix, breaking changes MUST be indicated by a ! immediately before the :. If ! is used, BREAKING CHANGE: MAY be omitted from the footer section, and the commit description SHALL be used to describe the breaking change.
14. Types other than feat and fix MAY be used in your commit messages, e.g., docs: updated ref docs.
15. The units of information that make up Conventional Commits MUST NOT be treated as case sensitive by implementors, with the exception of BREAKING CHANGE which MUST be uppercase.
16. BREAKING-CHANGE MUST be synonymous with BREAKING CHANGE, when used as a token in a footer.


## Reporting a bug

* Discussing the current state of the code.
* Submitting a fix.
* Proposing new features.
* Becoming a maintainer.
* We use GitHub to host code, to track issues and feature requests, as well as accept pull requests.

## Write bug reports with detail, background, and sample code

Great Bug Reports tend to have:

* A quick summary and/or background.
* Steps to reproduce.
* Be specific!
* Give sample code if you can. 
* What you expected would happen.
* What actually happens.
* Notes (possibly including why you think this might be happening, or stuff you tried that didn't work).

## All Code Changes Happen Through Pull Requests

Pull requests are the best way to propose changes to the codebase.

* Fork the repo and create your branch from master.
* If you've added code that should be tested, add tests.
* If you've changed APIs, update the documentation.
* Ensure the test suite passes.
* Make sure your code lints.
* Issue that pull request!
