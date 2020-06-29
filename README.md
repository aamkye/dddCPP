# dddCPP

dddCPP is part of dddNuker software which has ability to decode tachograf files of drivers and trucks from binary form to json form.

### Requirements:
- C++/Clang
- Cmake + make
- Ninja
- Python3
- UPX

### Build

- `git clean -fx`
- `git submodule update --init`
- `cmake -G Ninja .`
- `ninja`
- done

Or

- `git clean -fx`
- `git submodule update --init`
- `cmake .`
- `make`
- done

### GCC 7.3.0 Error

Orgins:

`src/utils/BVecHelper.cpp:61`

Will not pass:

```
auto ddd::BVecHelper::genericExtract(const size_t& offset) -> bVec {
  return bVec(bVecData.begin() + getOffSet(), bVecData.begin() + getOffSet(offset));
}
```

Will pass:

```
auto ddd::BVecHelper::genericExtract(const size_t& offset) -> bVec {
  std::vector<u_int8_t>::iterator beg = bVecData.begin() + getOffSet();
  std::vector<u_int8_t>::iterator end = bVecData.begin() + getOffSet(offset);
  return bVec(beg, end);
}
```

Backtrace:

```
/lib/x86_64-linux-gnu/libc.so.6(+0x18eb38)[0x7f9852ef7b38]
bin/DTTFP-DDD-TO-JSON(ddd::ObjectConvertTool::parseBCD(ddd::structure::general::rObj const&, unsigned long, unsigned long)+0x5d)[0x55d5e4a7601d]
bin/DTTFP-DDD-TO-JSON(ddd::Driver::parseIcc(std::vector<unsigned char, std::allocator<unsigned char> > const&)+0x25d)[0x55d5e4a2ce9d]
bin/DTTFP-DDD-TO-JSON(ddd::Driver::proceed()+0x1c4)[0x55d5e4a2f164]
bin/DTTFP-DDD-TO-JSON(ddd::Driver::Driver(std::map<unsigned int, ddd::structure::general::dataObj, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, ddd::structure::general::dataObj> > >)+0xf29)[0x55d5e4a30129]
bin/DTTFP-DDD-TO-JSON(ddd::Raw::Raw(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)+0x447)[0x55d5e4a3eef7]
bin/DTTFP-DDD-TO-JSON(main+0x95)[0x55d5e4a28435]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7)[0x7f9852d8ab97]
bin/DTTFP-DDD-TO-JSON(_start+0x2a)[0x55d5e4a2857a]
```
