# ACM
### Build the docs
```sh
$ cd docs
$ make html clean && make html
```

### To pdf

Install the environment
```sh
$ cd docs/source
$ conda createdoc update -f createdoc.yml
```

```sh
$ cd docs/source
$ rst2pdf index.rst acm.pdf
```