## Dependencies

* c++20
* [boost](https://www.boost.org)
* [sidmjson](https://github.com/simdjson/simdjson)

additionally you need to do

```shell
$ git submodule init
$ git submnodule update
```

since we are downloading here a bunch of libraries, this can take a while, so you can grab yourself a ☕️.

This approach is in particular useful, since most clusters don't allow the installation of packages.