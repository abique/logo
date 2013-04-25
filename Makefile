logo.svg: logo
	./logo >$@

logo: logo.cc
	$(CXX) -o $@ $<
