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

The [Ruby implementation][caro] is considered reference
and compatibility of this C implementation with the reference one
is ensured through [specs][spec].

## Building

```
cmake
make
make install
```

## License

dual-licensed: freely choose between GNU/LGPL 3 and MIT

[caro]: https://github.com/igneus/calendarium-romanum
[calapi]: https://github.com/igneus/church-calendar-api
[spec]: https://github.com/calendarium-romanum/spec
