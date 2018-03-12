package main

import (
	"encoding/base64"
	"fmt"
	"io/ioutil"
	"net/http"
	"os"
)

func Encode(path string) (string, error) {
	buff, err := ioutil.ReadFile(path)
	if err != nil {
		return "", err
	}

	return base64.StdEncoding.EncodeToString(buff), nil
}

func Decode(code string, dest string) error {
	buff, err := base64.StdEncoding.DecodeString(code)
	if err != nil {
		return err
	}
	if err := ioutil.WriteFile(dest, buff, 0777); err != nil {
		return err
	}
	return nil
}

func connectToServer(url string) {
	res, err := http.Get(url)
	if err != nil {
		fmt.Println("Bad connection!")
		return
	}

	content, err := ioutil.ReadAll(res.Body)
	res.Body.Close()
	if err != nil {
		fmt.Println("Bad connection!")
		return
	}
	fmt.Println(string(content))
}

func main() {
	code, err := Encode(os.Args[1])
	if err != nil {
		fmt.Println(err)
	} else {
		fmt.Println(code)
	}
}
