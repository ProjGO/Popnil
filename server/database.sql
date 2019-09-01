create database linpop;
use linpop;
create table `userinfo`
(
	`id` int,
	primary key (`id`),
	`passwd` varchar(32),
	`username` varchar(32),
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
	`idA` int,
	foreign key (`idA`) references `userinfo`(`id`),
	`idB` int,
	foreign key (`idB`) references `userinfo`(`id`),
	`anniversary` date
);
create table `membership`
(
	`gid` int,
	foreign key (`gid`) references `groupinfo`(`id`),
	`uid` int,
	foreign key (`uid`) references `userinfo`(`id`),
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
