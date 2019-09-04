drop database `linpop`;
create database `linpop`;
use `linpop`;
create table `userinfo`
(
	`id` int,
	primary key (`id`),
	`passwd` varchar(32) default '' not null,
	`nick` varchar(32) default '' not null,
	`portrait_idx` int default 0 not null,
	`bio` varchar(1024) default '' not null,
	`birthday` date not null,
	`ip` int default 0 not null,
	`connect` int default 0 not null
);
create table `groupinfo`
(
	`id` int,
	primary key (`id`),
	`name` varchar(32) default '' not null,
	`anniversary` date not null
);

create table `friendship`
(
	`idA` int,
	foreign key (`idA`) references `userinfo`(`id`),
	`idB` int,
	foreign key (`idB`) references `userinfo`(`id`),
	primary key (`idA`, `idB`),
	`anniversary` date not null
);
create table `tag`
(
	`masterid` int,
	`goalid` int,
	foreign key (`masterid`, `goalid`) references `friendship` (`idA`, `idB`),
	`text` varchar(32) default '' not null
);
create table `membership`
(
	`gid` int,
	foreign key (`gid`) references `groupinfo`(`id`),
	`uid` int,
	foreign key (`uid`) references `userinfo`(`id`),
	primary key (`gid`, `uid`),
	`permission` int default 2 not null,
	`anniversary` date not null
);

create table `usermessage`
(
	`time` timestamp not null,
	`masterid` int,
	`goalid` int,
	foreign key (`masterid`, `goalid`) references `friendship` (`idA`, `idB`),
	`text` varchar(1024) not null
);
create table `groupmessage`
(
	`time` timestamp not null,
	`masterid` int,
	`goalid` int,
	foreign key (`masterid`, `goalid`) references `membership` (`uid`, `gid`),
	`text` varchar(1024) not null
);
