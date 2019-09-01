###### clone repo and cd into it
```
git clone https://github.com/kevinGodell/lava-runner.git
cd lava-runner
```
###### create a _release_ build
```
mkdir release
cd release
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./lava_runner
```
###### create a _debug_ build
```
mkdir debug
cd debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
./lava_runner
````