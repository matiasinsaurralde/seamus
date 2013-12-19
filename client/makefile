all: main

arm: arm-main

main:	main.go
	GOOS=linux GOARCH=386 go build main.go

arm-main:	main.go
	GOOS=linux GOARCH=arm go build main.go
