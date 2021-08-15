# extrasampler

Collection of classes for extrapolation (or as some would say *prediction*) of new samples from slowly-sampled data. Written in C++.

## Implementation details

Currently two different extrapolation methods are available, implemented as class templates derived from a base one that defines the basic methods and interfaces. In short, they are:

- **Linear:** Works on a circular buffer of samples, and requires the number of samples it must work on.
- **Quadratic:** Works on two samples, but **sampling time must be constant** and provided.

All templates require at least the numerical type used (e.g *float* or *double*) to be instantiated.

Any more detailed explanation of the implementation can be inferred from the source files themselves.

## Usage

Since this library offers only class templates to instantiate, it is entirely made of headers that you can include.

## License

Copyright © 2021 Roberto Masocco, Marco Passeri
Please refer to the licensing information included in each file and to the LICENSE file provided.
