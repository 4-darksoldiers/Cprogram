extract:main.o fasta.so genbank.so
	cc -o extract main.o ./libfasta.so ./libgenbank.so

main.o:main.c cds.h fasta.h genbank.h
	cc -c main.c

fasta.so:fasta.c cds.h fasta.h
	cc fasta.c -shared -fPIC -o libfasta.so

genbank.so:genbank.c cds.h genbank.h
	cc genbank.c -shared -fPIC -o libgenbank.so

test:
	./extract genbank_raw.gb test.fasta

clean:
	rm extract main.o *.so *.fasta
