/* (Database Fundamentals, Assignment Part D, Spring  2024 */
/* script name: App.SQL */
/* purpose: Builds PostgreSQL tables for App database. The purpose is to store and manage information related to mobile applications, users, and app reviews to be able to track app information, manage user data and collect and review reviews.*/
/* date: 27 October 2024 */
/* The URL for the website related to this database is https://play.google.com/store/apps?hl=en_AU*/

--=================================================================================================
-- Drop the tables below
DROP TABLE IF EXISTS App;
DROP TABLE IF EXISTS AppUser;
DROP TABLE IF EXISTS AppReview;
--=================================================================================================
-- Create and insert into the tables below
CREATE TABLE App 
(   AppID serial NOT NULL,
    ContentRating varchar(10) not null CHECK (ContentRating IN ('G', 'PG', 'M', 'MA15+', 'R18+')),
    AppDescription text, 
    AppName varchar(100) not null,
    AppCompany varchar(100) not null, 
    AppPrice decimal(10, 2) not null, 
    ReleaseDate date not null, 
CONSTRAINT App_PK Primary Key (AppID)
);

CREATE TABLE AppUser
(   UserEmail varchar(100) NOT NULL, 
    UFName varchar(45), 
    ULName varchar(45), 
    UPassword varchar(100) not null, --(Generally encrypted/hashed)
    UStreetNo varchar(10),  -- In case of non-numeric characters
    UCity varchar(50), 
    UState char(3), 
    UCountry char(3) not null,   -- country ISO code
    UPostCode varchar(10),  -- Letters in postal code 
    UDOB date not null, 
    ULangPref char(2) not null,  -- Language code 
    UPhone varchar(15), 
CONSTRAINT User_PK Primary Key (UserEmail)
);

CREATE TABLE AppReview 
(   AppID serial NOT NULL,
    UserEmail varchar(100) NOT NULL, 
    ReviewDate DATE NOT NULL, 
    Comments text, 
    StarRating int not null check (StarRating >= 1 and StarRating <= 5),
CONSTRAINT AppReview_PK Primary Key (AppID, UserEmail, ReviewDate),
CONSTRAINT AppReview_FK1 Foreign Key (AppID) references App(AppID),
CONSTRAINT AppReview_FK2 Foreign Key (UserEmail) references AppUser(UserEmail)
);

INSERT into App values 
    (1, 'G', 'This is centered around a protagonist (you) that explores the wizarding world as an Auror, taking down Death Eaters one step at a time','Wizards unite','Portkey Inc', 0, '2024-09-09'),
    (2, 'R18+', 'This would be used to not only categorize the various flavors of beans, but also acts as a checklist that users can cross off', 'Bertie Botts','Berties Pty', 0.99, '2024-05-04'),
    (3, 'MA15+', 'Hello traveler, want to know the fastest broom in the west, or the first broomstick to ever be made, this app is for you. It also has a quiz for you to do for more fun','Hogwarts go' ,'Broomies Pty', 0, '2024-05-04'),
    (4, 'PG', 'Like to explore and feel a part of the Hogwarts magic, this app is not only for those interested in exploring the castle, but those who seek to interact with all sorts of magical figures and creatures', 'Ministry of Beasts','Portkey Inc', 2.50, '2024-05-04'), 
    (5, 'MA15+', 'Potions are hard to manage, much less remember, this app allows wizards and witches to never forget the ingredients and incantations of potion brewing','Potions and Brewers' ,'Broomies Pty', 1.00, '2024-05-04');

INSERT into AppUser values 
    ('Harry.potter@gmail.com', 'Harry', 'Potter', 'Dobbe123', 4, 'London', 'ENG', 'UK', 2562, '1980-07-31', 'EN', 426726272),
    ('ron.weasley@hotmail.com', 'Ronald', 'Weasley', 'Hermione12', 12, 'Bristol', 'ENG', 'UK', 7589, '1980-09-09', 'EN', 42312311),
    ('cho.chang@gmail.com', 'Cho', 'Chang', 'Raven12', 11, 'Edinburgh', 'SCT', 'UK', 8439, '1978-09-09', 'ZH', 42312311),
    ('tom.riddle@yahoo.com', 'Tom', 'Riddle', 'Salaza123', NULL, NULL, NULL, 'USA', 7548, '1949-09-08', 'HU', 4956454),
    ('Dobby.lovesSocks@gmail.com', 'Dobby', 'Elf', 'Socks456', 10, 'London', NULL, 'ENG', 4783, '1949-09-08', 'EN', 43537826);

INSERT into AppReview values 
    (1 , 'Harry.potter@gmail.com' , '2024-05-06' , 'This app is wicked awsome! Expeliarmous', '5'),
    (3 , 'Harry.potter@gmail.com' , '2024-05-10' , 'This app is like Voldemort! Yuck', '1'),
    (1  , 'ron.weasley@hotmail.com', '2024-04-05' , 'My freind recommended it to me, its ok' , '2'), 
    (5 , 'Dobby.lovesSocks@gmail.com' , '2023-06-06', 'its pretty cool needs more socks' , '4'),
    (3 , 'Dobby.lovesSocks@gmail.com' , '2022-09-09' , 'its one of the greatest things of my life' , '4'),
    (4 , 'cho.chang@gmail.com' , '2023-09-09' , 'It is one of my most used apps' , '5');

--=================================================================================================
-- Select * from TableName Statements
-- 2.b.1: Question: Get all apps and their information stored in the database
-- 2.b.1: SELECT statement: 
SELECT * from App;

-- 2.b.2: Question: Get all users and their information stored in the database
-- 2.b.2: SELECT statement:
SELECT * from AppUser;

-- 2.b.3: Question:  Get all appreviews stored in the database
-- 2.b.3: SELECT statement:
SELECT * from AppReview;

--=================================================================================================
-- 3.a: Question: What is the average rating for each app
-- 3.a: SELECT statement uinsg Group by:
select AppID, round(avg(StarRating), 1) as AvgRating 
from AppReview
Group by AppID
Order by AppID;

-- 3.b: Question: Get the reviews (comments) submitted by the users and which apps they belong to
-- 3.b: SELECT statement using Inner Join:
select AU.UserEmail, A.AppName, AR.Comments 
from AppUser AU inner join AppReview AR on AR.UserEmail = AU.UserEmail 
                inner join App A on A.AppID = AR.AppID;

-- 3.c: Question: List all apps that cost more than the average app price
-- 3.c: SELECT statement using Sub Query:
SELECT AppName, AppPrice
from App
where AppPrice > (select avg(AppPrice)
                    from App);
