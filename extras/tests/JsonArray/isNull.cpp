// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2023, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonArray::isNull()") {
  SECTION("returns true") {
    JsonArray arr;
    REQUIRE(arr.isNull() == true);
  }

  SECTION("returns false") {
    JsonDocument doc;
    JsonArray arr = doc.to<JsonArray>();
    REQUIRE(arr.isNull() == false);
  }
}

TEST_CASE("JsonArrayConst::isNull()") {
  SECTION("returns true") {
    JsonArrayConst arr;
    REQUIRE(arr.isNull() == true);
  }

  SECTION("returns false") {
    JsonDocument doc;
    JsonArrayConst arr = doc.to<JsonArray>();
    REQUIRE(arr.isNull() == false);
  }
}

TEST_CASE("JsonArray::operator bool()") {
  SECTION("returns false") {
    JsonArray arr;
    REQUIRE(static_cast<bool>(arr) == false);
  }

  SECTION("returns true") {
    JsonDocument doc;
    JsonArray arr = doc.to<JsonArray>();
    REQUIRE(static_cast<bool>(arr) == true);
  }
}

TEST_CASE("JsonArrayConst::operator bool()") {
  SECTION("returns false") {
    JsonArrayConst arr;
    REQUIRE(static_cast<bool>(arr) == false);
  }

  SECTION("returns true") {
    JsonDocument doc;
    JsonArrayConst arr = doc.to<JsonArray>();
    REQUIRE(static_cast<bool>(arr) == true);
  }
}
