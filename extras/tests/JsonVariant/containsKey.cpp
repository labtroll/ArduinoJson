// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2023, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <stdint.h>
#include <catch.hpp>

TEST_CASE("JsonVariant::containsKey()") {
  JsonDocument doc;
  JsonVariant var = doc.to<JsonVariant>();

  SECTION("containsKey(const char*)") {
    var["hello"] = "world";

    REQUIRE(var.containsKey("hello") == true);
    REQUIRE(var.containsKey("world") == false);
  }

  SECTION("containsKey(std::string)") {
    var["hello"] = "world";

    REQUIRE(var.containsKey(std::string("hello")) == true);
    REQUIRE(var.containsKey(std::string("world")) == false);
  }
}

TEST_CASE("JsonVariantConst::containsKey()") {
  JsonDocument doc;
  doc["hello"] = "world";
  JsonVariantConst cvar = doc.as<JsonVariant>();

  SECTION("containsKey(const char*) returns true") {
    REQUIRE(cvar.containsKey("hello") == true);
    REQUIRE(cvar.containsKey("world") == false);
  }

  SECTION("containsKey(std::string) returns true") {
    REQUIRE(cvar.containsKey(std::string("hello")) == true);
    REQUIRE(cvar.containsKey(std::string("world")) == false);
  }
}
