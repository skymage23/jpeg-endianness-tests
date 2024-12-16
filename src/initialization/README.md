Initialization code must not throw exceptions.

Initialization has its own error-handling code that is as basic as possible, and entirely error
code based. Re: Initialization sets up the generic error-handling structure, along with other
global structures, like the logging object.

Initialization must either be single threaded, or each segment therein must be responsible
for handling and waiting on its own threads. Re: to keep things simple and to provide
assurance that initialization subsegment that depends on another subsegment can 
have that assurance by means of the dependency subsegment being manually invoked
first. Dependency graphs must be strictly acyclic.