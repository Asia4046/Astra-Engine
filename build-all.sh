set echo on

echo "Building Everything..."

pushd engine
source build.sh
popd

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error:"$ERRORLEVEL && exit
fi 

pushd testbed 
source build.sh
popd 
ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then 
echo "Error:"$ERRORLEVEL && exit 
fi 

echo "ALL ASSEMBLIES BUILT SUCCESSFULLY."

version=0.0.1-dev-alpha

echo "Compressing Source Code and Build"
rm *.tar.gz
tar -zcvf build_and_source_$version.tar.gz *