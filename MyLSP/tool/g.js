var fs = require('fs')

var nameList = fs.readFileSync('./name.txt', {encoding: 'utf8'}).split('\r\n').filter(notEmpty)
var content = fs.readFileSync('./input.txt', {encoding: 'utf8'})
var segments = content.split(/\r\n\r\n/)
var nameMapList = []

segments.forEach(function(segment) {
	var name = /\w+\s+WSPAPI\s+(\w+)/.exec(segment)[1]
	var lowerName = inNameList(name)
	nameMapList.push({
		lower: lowerName,
		upper: name
	})
	console.log(lowerName)

	segment = segment.replace(name, lowerName)

	var outContent = 	'#include "Global.h"' + '\r\n' +
						'\r\n' +
						segment.replace(';', '') + '\r\n' +
						'{\r\n\treturn WSAEINVAL;\r\n}'
	fs.writeFileSync('out/' + lowerName + '.cpp', outContent)
})

var newContent = content
nameMapList.forEach(function(map) {
	newContent = newContent.replace(map.upper, map.lower)
})
fs.writeFileSync('out/WSP.h', '#pragma once\r\n\r\n' + newContent)

function notEmpty(item) {
	return item && true
}

function inNameList(name) {
	for (var i = 0; i < nameList.length; ++i) {
		if (nameList[i].toLowerCase() === name.toLowerCase()) {
			return nameList[i]
		}
	}
	return name
}