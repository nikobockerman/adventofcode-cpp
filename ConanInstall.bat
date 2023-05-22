conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h msvc-193 -pr:b default ^
 -s:h build_type=Release -s:h compiler.runtime_type=Release

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h msvc-193 -pr:b default ^
 -s:h build_type=RelWithDebInfo -s:h compiler.runtime_type=Release

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h msvc-193 -pr:b default ^
 -s:h build_type=MinSizeRel -s:h compiler.runtime_type=Release

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h msvc-193 -pr:b default ^
 -s:h build_type=Debug -s:h compiler.runtime_type=Debug

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h llvm-clang -pr:b default ^
 -s:h build_type=Release -s:h compiler.runtime_type=Release

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h llvm-clang -pr:b default ^
 -s:h build_type=RelWithDebInfo -s:h compiler.runtime_type=Release

:: Disabled due to some bug, likely in Conan with Ninja Multi-Config generator.
:: Similar issue #11115 https://github.com/conan-io/conan/issues/11115
::conan install . --update --build=missing ^
:: -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
:: -pr:h llvm-clang -pr:b default ^
:: -s:h build_type=MinSizeRel -s:h compiler.runtime_type=Release

conan install . --update --build=missing ^
 -c:h tools.cmake.cmake_layout:build_folder_vars="['settings.compiler']" ^
 -pr:h llvm-clang -pr:b default ^
 -s:h build_type=Debug -s:h compiler.runtime_type=Debug
