ArduinoJson: change log
=======================

HEAD
----

* Remove `BasicJsonDocument`
* Remove `StaticJsonDocument`
* Add abstract `Allocator` class
* Merge `DynamicJsonDocument` with `JsonDocument`
* Remove `JSON_ARRAY_SIZE()`, `JSON_OBJECT_SIZE()`, and `JSON_STRING_SIZE()`
* Remove `ARDUINOJSON_ENABLE_STRING_DEDUPLICATION` (string deduplication cannot be disabled anymore)
* Remove `JsonDocument::capacity()`
* Store the strings in the heap
* Reference-count shared strings
* Always store `serialized("string")` by copy (#1915)
* Remove the zero-copy mode of `deserializeJson()` and `deserializeMsgPack()`
* Fix double lookup in `to<JsonVariant>()`
* Fix double call to `size()` in `serializeMsgPack()`
* Include `ARDUINOJSON_SLOT_OFFSET_SIZE` in the namespace name
* Remove `JsonVariant::shallowCopy()`
* `JsonDocument`'s capacity grows as needed, no need to pass it to the constructor anymore
* `JsonDocument`'s allocator is not monotonic anymore, removed values get recycled
* Show a link to the documentation when user passes an unsupported input type
* Remove `JsonDocument::memoryUsage()`
* Remove `JsonDocument::garbageCollect()`
* Add `deserializeJson(JsonVariant, ...)` and `deserializeMsgPack(JsonVariant, ...)` (#1226)
* Call `shrinkToFit()` in `deserializeJson()` and `deserializeMsgPack()`
* `serializeJson()` and `serializeMsgPack()` replace the content of `std::string` and `String` instead of appending to it
* Replace `add()` with `add<T>()` (`add(T)` is still supported)
* Remove `createNestedArray()` and `createNestedObject()` (use `to<JsonArray>()` and `to<JsonObject>()` instead)

> ### BREAKING CHANGES
>
> As every major release, ArduinoJson 7 introduces several breaking changes.
> I added some stubs so that most existing programs should compile, but I highty recommend you upgrade your code.
>
> #### `JsonDocument`
> 
> In ArduinoJson 6, you could allocate the memory pool on the stack (with `StaticJsonDocument`) or in the heap (with `DynamicJsonDocument`).  
> In ArduinoJson 7, the memory pool is always allocated in the heap, so `StaticJsonDocument` and `DynamicJsonDocument` have been merged into `JsonDocument`.
>
> In ArduinoJson 6, `JsonDocument` had a fixed capacity; in ArduinoJson 7, it has an elastic capacity that grows as needed.
> Therefore, you don't need to specify the capacity anymore, so the macros `JSON_ARRAY_SIZE()`, `JSON_OBJECT_SIZE()`, and `JSON_STRING_SIZE()` have been removed.
>
> ```c++
> // ArduinoJson 6
> StaticJsonDocument<256> doc;
> // or
> DynamicJsonDocument doc(256);
> 
> // ArduinoJson 7
> JsonDocument doc;
> ```
>
> In ArduinoJson 7, `JsonDocument` reuses released memory, so `garbageCollect()` has been removed.  
> `shrinkToFit()` is still available and releases the over-allocated memory.
>
> Due to a change in the implementation, it's not possible to store a pointer to a variant from another `JsonDocument`, so `shallowCopy()` has been removed.
> 
> In ArduinoJson 6, the meaning of `memoryUsage()` was clear: it returned the number of bytes used in the memory pool.  
> In ArduinoJson 7, the meaning of `memoryUsage()` would be ambiguous, so it has been removed.
>
> #### Custom allocators
>
> In ArduinoJson 6, you could specify a custom allocator class as a template parameter of `BasicJsonDocument`.  
> In ArduinoJson 7, you must inherit from `ArduinoJson::Allocator` and pass a pointer to an instance of your class to the constructor of `JsonDocument`.
>
> ```c++
> // ArduinoJson 6
> class MyAllocator {
>   // ...
> };
> BasicJsonDocument<MyAllocator> doc(256);
>
> // ArduinoJson 7
> class MyAllocator : public ArduinoJson::Allocator {
>   // ...
> };
> MyAllocator myAllocator;
> JsonDocument doc(&myAllocator);
> ```
>
> #### `createNestedArray()` and `createNestedObject()`
>
> In ArduinoJson 6, you could create a nested array or object with `createNestedArray()` and `createNestedObject()`.  
> In ArduinoJson 7, you must use `add<T>()` or `to<T>()` instead.
>
> For example, to create `[[],{}]`, you would write:
>
> ```c++
> // ArduinoJson 6
> doc.createNestedArray("array");
> doc.createNestedObject("object");
>
> // ArduinoJson 7
> doc.add<JsonArray>();
> doc.add<JsonObject>();
> ```
>
> And to create `{"array":[],"object":{}}`, you would write:
>
> ```c++
> // ArduinoJson 6
> doc.createNestedArray("array");
> doc.createNestedObject("object");
>
> // ArduinoJson 7
> doc["array"].to<JsonArray>();
> doc["object"].to<JsonObject>();
> ```
