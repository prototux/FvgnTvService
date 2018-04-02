#!/usr/bin/env bash

while read o_call; do
	func_name=$(echo "$o_call" | cut -d',' -f3 | cut -d')' -f1)
	file_name=$(echo "$func_name" | cut -d'_' -f2)
	file_up=$(echo "$file_name" | tr '[:lower:]' '[:upper:]')

	#echo -en "#ifndef __API_${file_up}_H__\n#define __API_${file_up}_H__\n\n#include <onion/onion.h>\n#include <onion/request.h>\n#include <onion/response.h>\n\n#endif /* __API_${file_up}_H__ */" > ./api_${file_name}.h

	#echo "onion_connection_status ${func_name}(void *unused, onion_request *req, onion_response *res);"

	echo -en "#include <stdlib.h>\n#include <stdio.h>\n#include <inttypes.h>\n#include <string.h>\n\n#include <onion/onion.h>\n#include <onion/dict.h>\n#include <onion/block.h>\n#include <onion/request.h>\n#include <onion/response.h>\n#include <onion/url.h>\n#include <onion/low.h>\n\n#include \"tools.h\"\n#include \"api.h\"\n\n" > ./api_${file_name}.c

	echo -en "onion_connection_status ${func_name}(void *unused, onion_request *req, onion_response *res)\n{\n\tAPI_UNIMPLEMENTED\n}\n\n"

done< <(cat ./main.c | grep "//onion_url_add")
