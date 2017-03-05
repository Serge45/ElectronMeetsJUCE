
distPath="$SRCROOT/dist/"

if [ -d "$distPath" ]; then
echo "Dist folder exists."
else
echo "Create dist folder."
mkdir "$distPath"
fi

nativePath="$distPath/native/"

if [ -d "$nativePath" ]; then
echo "Native folder exists."
else
echo "Create native folder."
mkdir "$nativePath"
fi

cp $BUILT_PRODUCTS_DIR/*.node $nativePath
