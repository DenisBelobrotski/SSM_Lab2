cmake_minimum_required(VERSION 3.12)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp BernoulliModel.cpp BernoulliModel.h PRNG.h MultiplicativePRNG.cpp MultiplicativePRNG.h NegativeBinomialModel.cpp NegativeBinomialModel.h DistributionModel.h HelperFunctions.cpp)