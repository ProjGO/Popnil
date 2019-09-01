grant select, insert, update, delete, create, drop
	on `linpop`.*
	to 'ProjGO'@'localhost'
	identified by '1234';
drop database `linpop`;
create database `linpop`;
use `linpop`;
create table `userinfo`
(
	`id` int,
	primary key (`id`),
	`passwd` varchar(32),
	`nick` varchar(32),
	`bio` varchar(1024),
	`birthday` date,
	`ip` int,
	`connect` int
);
create table `groupinfo`
(
	`id` int,
	primary key (`id`),
	`anniversary` date
);
create table `friendship`
(
	`idord` int,
	foreign key (`idord`) references `userinfo`(`id`),
	`idnew` int,
	foreign key (`idnew`) references `userinfo`(`id`),
	check (`idord` < `idnew`),
	primary key (`idord`, `idnew`),
	`anniversary` date
);
create table `membership`
(
	`gid` int,
	foreign key (`gid`) references `groupinfo`(`id`),
	`uid` int,
	foreign key (`uid`) references `userinfo`(`id`),
	primary key (`gid`, `uid`),
	permission int
);
create table `usermessage`
(
	`time` timestamp,
	`masterid` int,
	foreign key (`masterid`) references `userinfo`(`id`),
	`goalid` int,
	foreign key (`goalid`) references `userinfo`(`id`),
	`text` varchar(1024)
);
create table `groupmessage`
(
	`time` timestamp,
	`masterid` int,
	foreign key (`masterid`) references `userinfo`(`id`),
	`goalid` int,
	foreign key (`goalid`) references `groupinfo`(`id`),
	`text` varchar(1024)
);
