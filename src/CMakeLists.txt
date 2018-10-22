add_executable(TestFileIO TestFileIO.cpp FileIO.cpp)

add_executable(TestFNoise TestFNoise.cpp fnoise.cpp)

add_executable(TestNoiseGeneration  TestNoiseGeneration.cpp
                                    FileIO.cpp
                                    fnoise.cpp
                                    HarmonicNoiseGenerator.cpp
                                    PinkNoiseGenerator.cpp
                                    PedestalNoiseGenerator.cpp)

add_executable(TestHarmonicNoiseGenerator TestHarmonicNoiseGenerator.cpp HarmonicNoiseGenerator.cpp)