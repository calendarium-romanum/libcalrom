# libcalrom

C library for calendar computations according to
the Roman Catholic liturgical calendar as instituted by
[MP Mysterii Paschalis](http://w2.vatican.va/content/paul-vi/en/motu_proprio/documents/hf_p-vi_motu-proprio_19690214_mysterii-paschalis.html) of Paul VI. (AAS 61 (1969), pp. 222-226).
The rules are defined in
*General Norms for the Liturgical Year and the Calendar*
([English translation][gnlyc]).

After the calendar has been implemented [in Ruby][caro]
and the results made widely available for remote access
through an [API][calapi],
this library implements the same functionality in C.
The main intent is to allow easy creation of bindings for widest
possible spectrum of programming languages.

## Requirements

* glib 2.0
* cmake (used for building in the current alpha stage; later switch to autotools is probable)

## Building

```
cmake .
make
make install
```

## Running tests

Unit tests of libcalrom are built upon the
[glib testing framework](https://developer.gnome.org/glib/stable/glib-Testing.html).

The build process described above also builds executable `tests/run`
which can be run on it's own or using
[`gtester`](https://developer.gnome.org/glib/stable/gtester.html).

There is further a separate project with ["acceptance tests"][spec]
ensuring that libcalrom's behaviour is consistent
with the Ruby gem [calendarium-romanum][caro],
which is considered reference implementation of the calendar system.
Directory [spec_cli/](./spec_cli) contains an adapter for this
test suite.

## License

dual-licensed: freely choose between GNU/LGPL 3 and MIT

[caro]: https://github.com/igneus/calendarium-romanum
[calapi]: https://github.com/igneus/church-calendar-api
[spec]: https://github.com/calendarium-romanum/spec
