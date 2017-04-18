cd build
cmake ..
make -j4
mv raytrace ..
cd ..
echo
echo
echo
./raytrace $@
rm raytrace
