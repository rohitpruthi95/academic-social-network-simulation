system("python readml.py");
system("./solve FW");

print qq(Enter "exit" to stop processing queries otherwise enter your quries.\n);
print qq(Enter the name of any university in double quotes eg. "IITD" and the student ID should be a number (without quotes)\n);


sub understand{

	$x = @_[0];
	@id = $x =~ /(\d+)/g;
	@univ = $x =~ m/"(.*?)"/g; 
	if (index($x, 'CLIQUE') != -1) {
		system("./solve CL @univ[0] @id[0]");
	}
	elsif (index($x, 'SHORTEST') != -1 || index($x, 'DISTANCE') != -1) {
		if(scalar @id == 2){
			if(index($x, 'DISTANCE') != -1 || index($x, 'LENGTH') != -1){
				if(scalar @univ >= 2){
					system("./solve SD @univ[0] @id[0] @univ[1] @id[1]");
				}
				else{
					system("./solve SD @univ[0] @id[0] @univ[0] @id[1]");
				}
			}
			else {
				if(scalar @univ >= 2){
					system("./solve SP @univ[0] @id[0] @univ[1] @id[1]");
				}
				else{
					system("./solve SP @univ[0] @id[0] @univ[0] @id[1]");
				}
				
			}
		}
		else{
			system("./solve SD");
		}
	}
	elsif (index($x, 'IMPORTAN') != -1) {
		if(index($x, 'MORE') != -1 || index($x, 'MOST') != -1){
			system("./solve CI @univ[0] @id[0]");
		} 	
		else{
			system("./solve I @univ[0] @id[0]");
		}
	}
	else{
		print qq(Query not recognized, please try again.\n);
	}
}

while(true){
	$inp = <STDIN>; 
	$inp = uc $inp;
	last if($inp eq "EXIT\n"); 
	understand($inp); 
}
