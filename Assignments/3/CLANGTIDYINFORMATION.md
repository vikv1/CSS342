I disabled a lot of llvm checks and other checks like no recursion, and others 
that conflict with the standard that most people code with.

Running on the linux lab, all warnings from clang tidy are suppressed
due to them being from system headers. Please make sure that the provided clang tidy
file is being run, as it is not producing any warnings caused by me.

This is the output when tested on the linux lab w/ the provided simplecompile script:
113895 warnings generated.
Suppressed 113895 warnings (113895 in non-user code).