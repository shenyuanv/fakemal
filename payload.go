package main

import (
	"fmt"
	"io/ioutil"
	"net/http"

	"github.com/jasonlvhit/gocron"
)

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
	s := gocron.NewScheduler()
	s.Every(3).Seconds().Do(connectToServer, "http://www.exampie.com")
	s.Every(3).Seconds().Do(connectToServer, "http://izlinix.com")
	s.Every(3).Seconds().Do(connectToServer, "http://agroluftbild.de")
	s.Every(3).Seconds().Do(connectToServer, "http://dinkelbrezel.de")
	<-s.Start()
}
