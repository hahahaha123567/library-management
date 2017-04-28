create database library;

use database library;

create table book
(
	id varchar(50),
	category varchar(50),
	name varchar(50),
	press varchar(50),
	year varchar(50),
	author varchar(50),
	price float,
	total int,
	stock int
)

create table admin 
(
	id varchar(50),
	password varchar(50),
	name varchar(50),
	contact varchar(50)
)

create table borrow
(
	id varchar(50),
	card varchar(50),
	borrow_date date,
	return_date date,
	admin varchar(50)
)

create table card
(
	number varchar(50),
	name varchar(50),
	company varchar(50),
	category varchar(50)
)