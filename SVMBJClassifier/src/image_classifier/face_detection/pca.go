package main

import "gocv.io/x/gocv"

func PCA(m gocv.Mat) {
	covar := gocv.NewMat()
	mean := gocv.NewMat()
	gocv.CalcCovarMatrix(m, &covar, &mean, gocv.CovarRows, gocv.MatTypeCV64F)
}
