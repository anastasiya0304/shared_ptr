#include "shared_ptr.hpp"
#include <catch.hpp>

SCENARIO("Init", "[Init]"){
  shared_ptr<int> a;
  REQUIRE(a.use_count() == 0);
  REQUIRE(a.get() == nullptr);
  REQUIRE(!bool(a));
}

SCENARIO("with parameteres", "[with param]"){
  shared_ptr<int> a(new int(5));
  REQUIRE(a.use_count() == 1);
  REQUIRE(*a == 5);
  REQUIRE(a.unique());
  //REQUIRE(a);
}

SCENARIO("copy constructor", "[copy c]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b(a);
  REQUIRE(*b == 5);
  REQUIRE(b.use_count() == 2);
}

SCENARIO("copy operator", "[copy o]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b;
  b = a;
  REQUIRE(*b == 5);
  REQUIRE(b.use_count() == 2);
}

SCENARIO("move constructor", "[move c]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b(std::move(a));
  REQUIRE(*b == 5);
  REQUIRE(a.get() == nullptr);
  REQUIRE(b.use_count() == 1);
  REQUIRE(a.use_count() == 0);  
}

SCENARIO("move operator", "[move o]"){
  shared_ptr<size_t> f_sp(new size_t[10]);
	auto s_sp = std::move(f_sp);

	REQUIRE(f_sp.get() == nullptr);
	REQUIRE(f_sp.use_count() == 0);
	REQUIRE(f_sp.unique() == false);

	REQUIRE(s_sp.get() != nullptr);
	REQUIRE(s_sp.use_count() == 1);
	REQUIRE(s_sp.unique() == true);
}

SCENARIO("reset", "[reset]"){
  shared_ptr<int> a(new int(5));
  a.reset();
  REQUIRE(a.use_count() == 0);
  REQUIRE(a.get() == nullptr);
}
