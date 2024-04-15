# When you run this script, every file in the current directory will be processed into a .cpp and .h file. These two files can then be imported and embedded into the game as assets.

for file in *; do
    if [ -f "$file" ]; then
        filename="${file%.*}" # Extract filename without extension
        extension="${file##*.}" # Extract file extension

        # Convert the file to a C++ file using xxd
		echo "#include \"${filename}.h\"" > "$filename.cpp"
		echo "" >> "$filename.cpp"
        xxd -i "$file" >> "$filename.cpp"
		
		# Set the two initial underscores based on whether the filename starts with a number
		if [[ $filename =~ ^[0-9] ]]; then
			us="__"
		else
			us=""
		fi
		
		# Create a header file for the C++ file
		echo "extern unsigned char ${us}${filename}_${extension}[];" > "$filename.h"
		echo "extern unsigned int ${us}${filename}_${extension}_len;" >> "$filename.h"
    fi
done
