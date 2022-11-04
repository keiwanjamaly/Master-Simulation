## Dependencies

* c++20
* [boost](https://www.boost.org)
* [sidmjson](https://github.com/simdjson/simdjson)

The project is structured in a way, that you don't need to install anything except c++20. Everything else is organized
in submodules, so you just need to do

```shell
$ git submodule init
$ git submnodule update
```

since we are downloading here a bunch of libraries, this can take a while, so you can grab yourself a ☕️.

This approach is in particular useful, since most clusters don't allow the installation of packages.