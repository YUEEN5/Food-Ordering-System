-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jan 23, 2024 at 11:11 AM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.0.28

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `fos_ws1`
--

-- --------------------------------------------------------

--
-- Table structure for table `account`
--

CREATE TABLE `account` (
  `ACCOUNT_ID` int(11) NOT NULL,
  `CUST_ID` int(11) DEFAULT NULL,
  `STAFF_ID` int(11) DEFAULT NULL,
  `ADMINROLE` tinyint(1) NOT NULL DEFAULT 0,
  `USERNAME` varchar(100) NOT NULL,
  `PASSWORD` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `account`
--

INSERT INTO `account` (`ACCOUNT_ID`, `CUST_ID`, `STAFF_ID`, `ADMINROLE`, `USERNAME`, `PASSWORD`) VALUES
(100001, NULL, 50001, 1, 'joanne', '123abc'),
(100002, 300001, NULL, 0, 'amirul', 'abc123\r\n'),
(100003, 300002, NULL, 0, 'kuang123', 'kzkz123'),
(100004, 300003, NULL, 0, 'nurin', 'nurin12345'),
(100005, 300004, NULL, 0, 'donglin', 'ldl123'),
(100006, 300005, NULL, 0, 'jenny123', '123123'),
(100007, 300006, NULL, 0, 'tiben5', 'tiben123'),
(100008, NULL, 50002, 1, 'Evelyn', 'abc321'),
(100009, 300007, NULL, 0, 'siti', 'siti456'),
(100010, 300008, NULL, 0, 'ahmad', 'ahmad789'),
(100011, 300009, NULL, 0, 'rachel', 'rachel321'),
(100012, 300010, NULL, 0, 'alex', 'alex654'),
(100013, 300011, NULL, 0, 'amina', 'amina987'),
(100015, 300012, NULL, 0, 'ahmadshah', 'abc123'),
(100016, 300013, NULL, 0, 'noraini', 'noraini456'),
(100017, 300014, NULL, 0, 'jeffreytan', 'jeffreytan789'),
(100018, 300015, NULL, 0, 'lindalee', 'lindalee123'),
(100020, NULL, 50005, 1, 'GaryAdmin', 'admin789'),
(100021, 300016, NULL, 0, 'mohdazlan', 'mohdazlan456'),
(100022, 300017, NULL, 0, 'zulaikha', 'zulaikha789'),
(100023, 300018, NULL, 0, 'arifamir', 'arifamir123'),
(100024, 300019, NULL, 0, 'ninaabdullah', 'ninaabdullah456'),
(100025, 300020, NULL, 0, 'stevenchong', 'stevenchong789'),
(100026, 300021, NULL, 0, 'sarahlim', 'sarahlim123'),
(100027, 300022, NULL, 0, 'amirahhassan', 'amirahhassan456'),
(100028, 300023, NULL, 0, 'adamng', 'adamng789'),
(100029, 300024, NULL, 0, 'aishahrahim', 'aishahrahim123'),
(100030, 300025, NULL, 0, 'danielyap', 'abc789'),
(100031, 300026, NULL, 0, 'fatinaziz', 'fatinaziz123'),
(100032, 300027, NULL, 0, 'benjaminlim', 'benjaminlim456'),
(100033, 300028, NULL, 0, 'elinatan', 'elinatan789'),
(100034, 300030, NULL, 0, 'aaaaa', 'aaaaa'),
(100035, 300031, NULL, 0, 'lyana', '12345'),
(100036, NULL, 50006, 1, 'jenny', 'jenny123'),
(100037, NULL, 50007, 1, 'ahmed', 'ahmed123');

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `CUST_ID` int(11) NOT NULL,
  `CIC` varchar(30) NOT NULL,
  `CNAME` varchar(100) NOT NULL,
  `CPHONE_NO` varchar(30) NOT NULL,
  `CEMAIL` varchar(100) NOT NULL,
  `CADDRESS` varchar(100) NOT NULL,
  `CGENDER` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`CUST_ID`, `CIC`, `CNAME`, `CPHONE_NO`, `CEMAIL`, `CADDRESS`, `CGENDER`) VALUES
(300001, '021005-03-1045', 'Amirul Abdullah', '012-394 2093', 'amirul@gmail.com', 'No.15, Jalan Tuah, Melaka', 'Male'),
(300002, '010329-12-1029', 'Kang Ze', '011-3025 7293', 'kangze@gmail.com', 'No.10, Jalan Durian, Taman Bukit Beruang', 'male'),
(300003, '980610-01-1026', 'Nurin Athirah', '010-334 7293', 'athirah@gmail.com', 'No.10, Jalan Hang Tuah, Melaka', 'female'),
(300004, '010305-02-1087', 'Lim Dong Lin', '011-3025 7893', 'ldl@gmail.com', 'No.10, Jalan Durian, Taman Hang Jaya, Melaka', 'male'),
(300005, '800115-07-3024', 'Jenny Lim', '011-3025 7293', 'kangze@gmail.com', 'No.10, Jalan Durian, Taman Bukit Beruang', 'female'),
(300006, '020219-02-0283', 'Amirul', '012-302 9675', 'amirul@gmail.com', 'No.15, Jalan Makmur, Taman Bukit Beruang', 'male'),
(300007, '011223-08-4567', 'Siti Aishah', '013-456 8901', 'siti.aishah@example.com', 'No.7, Jalan Bunga Raya', 'female'),
(300008, '930511-07-1234', 'Ahmad Bin Hassan', '017-976 5432', 'ahmad.hassan@example.com', 'No.15, Jalan Merdeka, Melaka', 'male'),
(300009, '870625-12-7890', 'Rachel Lee', '019-124 5678', 'rachel.lee@example.com', 'No.22, Jalan Seri Gemilang, Melaka', 'female'),
(300010, '040402-03-6789', 'Alex Tan', '016-875 4321', 'alex.tan@example.com', 'No.5, Jalan Harmoni, Melaka', 'male'),
(300011, '051215-09-3456', 'Amina Mohd', '014-245 6789', 'aminana@gmail.com', 'No.11, Jalan Cemerlang, Melaka', 'female'),
(300012, '871214-08-1234', 'Ahmad Shah', '019-134 5678', 'ahmad.shah@example.com', 'No.12, Jalan Bunga Raya, Malacca', 'male'),
(300013, '920601-07-2345', 'Noraini Mohd', '017-345 6789', 'noraini.mohd@example.com', 'No.5, Jalan Merdeka, Melaka', 'female'),
(300014, '811031-12-3456', 'Jeffrey Tan', '016-456 7890', 'jeffrey.tan@example.com', 'No.22, Jalan Seri Gemilang, Melaka', 'male'),
(300015, '950505-03-4567', 'Linda Lee', '014-467 8901', 'linda.lee@example.com', 'No.15, Jalan Harmoni, Melaka', 'female'),
(300016, '041205-09-5678', 'Mohd Azlan', '013-578 9012', 'azlan@example.com', 'No.11, Jalan Cemerlang', 'male'),
(300017, '871214-08-6789', 'Siti Zulaikha', '012-789 0123', 'zulaikha@example.com', 'No.7, Jalan Bunga Raya', 'female'),
(300018, '920601-07-7890', 'Arif Amir', '019-7890 134', 'arif.amir@example.com', 'No.5, Jalan Merdeka, Melaka', 'male'),
(300019, '811031-12-8901', 'Nina Abdullah', '017-801 2345', 'nina.abdullah@example.com', 'No.22, Jalan Seri Gemilang', 'female'),
(300020, '950505-03-9012', 'Steven Chong', '016-912 3456', 'steven.chong@example.com', 'No.15, Jalan Harmoni, Melaka', 'male'),
(300021, '041205-09-1234', 'Sarah Lim', '014-128 4678', 'sarah.lim@example.com', 'No.11, Jalan Cemerlang, Melaka', 'female'),
(300022, '871214-08-2345', 'Amirah Hassan', '012-345 6789', 'amirah.hassan@example.com', 'No.7, Jalan Bunga Raya', 'female'),
(300023, '920601-07-3456', 'Adam Ng', '019-346 7890', 'adam.ng@example.com', 'No.5, Jalan Merdeka, Melaka', 'male'),
(300024, '811031-12-4567', 'Aishah Rahim', '017-567 8901', 'aishah.rahim@example.com', 'No.22, Jalan Seri Gemilang', 'female'),
(300025, '950505-03-5678', 'Daniel Yap', '016-578 9012', 'daniel.yap@example.com', 'No.15, Jalan Harmoni, Melaka', 'male'),
(300026, '041205-09-6789', 'Fatin Aziz', '014-679 0123', 'fatin.aziz@example.com', 'No.11, Jalan Cemerlang, Melaka', 'female'),
(300027, '871214-08-8901', 'Benjamin Lim', '012-801 2345', 'benjamin.lim@example.com', 'No.7, Jalan Bunga Raya, Melaka', 'male'),
(300028, '920601-07-9012', 'Elina Tan', '019-902 3456', 'elina.tan@example.com', 'No.5, Jalan Merdeka, Melaka', 'female'),
(300029, '811031-12-1234', 'Rahman Jamal', '012-345 2034', 'rahman.jamal@example.com', 'No.22, Jalan Seri Gemilang, Melaka', 'male'),
(300030, '010101-01-2034', 'Najihah', '012-213 2222', '1', '1', 'Female'),
(300031, '010115-10-2034', 'Lyanya', '012-304 2934', 'lyana@gmail.com', 'No.10, Jalan Bahagia, Yuji', 'Female');

-- --------------------------------------------------------

--
-- Table structure for table `feedback`
--

CREATE TABLE `feedback` (
  `FEEDBACK_ID` int(11) NOT NULL,
  `ORDER_ID` int(11) NOT NULL,
  `CUST_ID` int(11) NOT NULL,
  `RATING` int(11) NOT NULL,
  `COMMENTS` varchar(500) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `feedback`
--

INSERT INTO `feedback` (`FEEDBACK_ID`, `ORDER_ID`, `CUST_ID`, `RATING`, `COMMENTS`) VALUES
(900001, 800002, 300001, 4, 'good but spicy'),
(900002, 800019, 300010, 3, 'not so delicious, but worthy'),
(900022, 800001, 300003, 4, 'The delivery was on time, and the food was delicious!'),
(900023, 800003, 300002, 2, 'The order quantity seems too high, please double-check.'),
(900024, 800004, 300002, 4, 'The wedges were delicious, but a bit more would have been perfect.'),
(900025, 800005, 300004, 3, 'The additional egg was missing from the order.'),
(900026, 800007, 300005, 5, 'Great taste and prompt delivery. No complaints.'),
(900027, 800008, 300002, 4, 'Good service, but the delivery time could be improved.'),
(900028, 800017, 300020, 3, 'The order was missing onions as requested.'),
(900029, 800018, 300011, 5, 'The spicy level 3 was perfect!'),
(900030, 800026, 300017, 5, 'The extra sauce was included as requested. Thank you!'),
(900031, 800027, 300011, 3, 'The onions were missing from the order.'),
(900032, 800020, 300026, 5, 'No issues, the food arrived as expected.'),
(900033, 800047, 300017, 5, 'The online banking pick-up process was smooth.'),
(900034, 800048, 300011, 3, 'The food was good, but the request for no spicy was not followed.'),
(900035, 800049, 300011, 4, 'The order was correct, but more garlic would have been better.'),
(900036, 800050, 300010, 2, 'The order was not as expected. Disappointed with the quality.'),
(900037, 800011, 300005, 3, 'The order was fine, but the food could have been warmer.'),
(900038, 800012, 300003, 5, 'Excellent service and tasty food!'),
(900039, 800032, 300023, 5, 'Great taste and prompt delivery. No complaints.'),
(900040, 800033, 300009, 3, 'The extra cheese was not noticeable.'),
(900041, 800052, 300024, 3, 'good'),
(900042, 800031, 300005, 4, 'The taste is good! I got discount!'),
(900043, 800057, 300031, 2, 'i don\'t like it');

-- --------------------------------------------------------

--
-- Table structure for table `menu`
--

CREATE TABLE `menu` (
  `MENU_ID` varchar(10) NOT NULL,
  `NAME` varchar(30) NOT NULL,
  `DESCRIPTION` varchar(100) NOT NULL,
  `PRICE` double NOT NULL,
  `STATUS` varchar(30) NOT NULL DEFAULT 'UNAVAILABLE'
) ;

--
-- Dumping data for table `menu`
--

INSERT INTO `menu` (`MENU_ID`, `NAME`, `DESCRIPTION`, `PRICE`, `STATUS`) VALUES
('F0001', ' Nasi Lemak Supreme', 'Coconut rice with plant-based anchovies, peanuts, boiled eggs, and sambal', 15.7, 'AVAILABLE'),
('F0002', 'Penang Laksa', 'Spicy noodle soup with coconut milk, tofu, and a medley of herbs', 11.75, 'UNAVAILABLE'),
('F0003', 'Japanese Curry Udon', 'Udon noodles in a sweet and slightly spicy Japanese curry broth with potatoes', 14.9, 'AVAILABLE'),
('F0004', 'Bibimbap Bowl', 'Korean mixed rice bowl with tofu, assorted vegetables, and gochujang sauce', 11.5, 'UNAVAILABLE'),
('F0005', 'Satay Skewers', 'Grilled tofu skewers with peanut sauce and cucumber relish', 8.75, 'AVAILABLE'),
('F0006', 'Char Kway Teow', 'Stir-fried flat rice noodles with tofu, bean sprouts, and Chinese chives', 12.99, 'AVAILABLE'),
('F0007', 'Hainanese Chicken Rice', 'Mock chicken with fragrant rice, ginger, and chili sauce', 13.75, 'UNAVAILABLE'),
('F0008', 'Rendang Puffs', 'Mini pastry puffs filled with flavorful vegan rendang', 9.5, 'UNAVAILABLE'),
('F0009', 'Roti Canai with Curry', 'Flaky flatbread served with vegetarian curry sauce', 10.99, 'AVAILABLE'),
('F0010', 'Kampung Fried Rice', 'Spicy fried rice with a mix of local flavors', 12.5, 'UNAVAILABLE'),
('F0011', 'Mushroom burger', 'Delicious mushroom burger served with a coke and wedges', 10.3, 'AVAILABLE'),
('F0012', 'Lontong', 'Traditional dish with compressed rice in a spicy coconut broth', 12.5, 'UNAVAILABLE'),
('F0013', 'Spaghetti Aglio Olio', 'Classic Italian pasta with a garlic-infused olive oil sauce', 15.3, 'AVAILABLE'),
('F0014', 'Mango Sticky Rice', 'Sweet sticky rice topped with fresh mango slices and coconut sauce', 9.9, 'AVAILABLE'),
('F0015', 'Satay Skewers', 'Grilled tofu skewers with peanut sauce and cucumber relish', 13.9, 'UNAVAILABLE'),
('F0016', 'Pad Thai', 'Stir-fried rice noodles with tofu, peanuts, and lime', 11.5, 'AVAILABLE'),
('F0017', 'Vegetarian Bak Kut Teh', 'herbal soup with vegetarian mock meat, mushrooms and taufu', 15.9, 'AVAILABLE'),
('F0018', 'Vegan Roti Jala', 'Lace pancake served with vegan curry for dipping', 8.5, 'UNAVAILABLE'),
('F0019', 'Mushroom Pizza', 'Pizza topped with mushroom rendang, bell peppers, and onions', 15.99, 'AVAILABLE'),
('F0020', 'Vegan Sushi Platter', 'Assorted vegan sushi rolls with avocado, cucumber, and pickled radish', 14.5, 'AVAILABLE'),
('F0021', 'Fries Set', 'with curly fries, wedges, waffle fries, and creamy sauce', 12.9, 'UNAVAILABLE');

-- --------------------------------------------------------

--
-- Table structure for table `orderlist`
--

CREATE TABLE `orderlist` (
  `ORDER_ID` int(11) NOT NULL,
  `MENU_ID` varchar(5) NOT NULL,
  `CUST_ID` int(11) NOT NULL,
  `REMARK` varchar(100) DEFAULT NULL,
  `TOTAL_PRICE` double NOT NULL,
  `QUANTITY` int(11) NOT NULL,
  `PAYMETHOD` varchar(30) NOT NULL,
  `DELIVERY` varchar(20) NOT NULL,
  `PROMOCODE` int(11) DEFAULT NULL,
  `DISCOUNT` double DEFAULT NULL,
  `ORDER_DATE` datetime DEFAULT NULL,
  `ADDRESS` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `orderlist`
--

INSERT INTO `orderlist` (`ORDER_ID`, `MENU_ID`, `CUST_ID`, `REMARK`, `TOTAL_PRICE`, `QUANTITY`, `PAYMETHOD`, `DELIVERY`, `PROMOCODE`, `DISCOUNT`, `ORDER_DATE`, `ADDRESS`) VALUES
(800001, 'F0011', 300003, '', 32.9, 3, 'Cash', 'Delivery', 0, 0, '2024-01-06 22:28:28', 'No.10, Jalan Hang Tuah, Melaka'),
(800002, 'F0003', 300001, 'no egg please', 29.8, 2, 'Tng Ewallet', 'Pick Up', 0, 0, '2024-01-06 22:30:10', 'NULL'),
(800003, 'F0003', 300002, '', 298, 20, 'Tng Ewallet', 'Pick Up', 0, 0, '2024-01-07 03:27:14', 'NULL'),
(800004, 'F0011', 300002, 'more wedges', 51.5, 5, 'Cash', 'Pick Up', 0, 0, '2024-01-07 03:29:27', 'NULL'),
(800005, 'F0010', 300004, 'add egg', 75, 6, 'Online Banking', 'Pick Up', 0, 0, '2024-01-07 03:40:27', 'NULL'),
(800007, 'F0012', 300005, NULL, 12.5, 1, 'Cash', 'Delivery', 0, 0, '2023-11-08 08:16:42', 'No. 13, Jalan Muhibah, Melaka'),
(800008, 'F0001', 300002, NULL, 32, 3, 'Cash', 'Delivery', 0, 0, '2022-01-08 12:30:00', 'No.10, Jalan Durian, Bukit Beruang'),
(800009, 'F0002', 300011, NULL, 59.96, 4, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-01-08 12:35:00', 'NULL'),
(800010, 'F0003', 300004, NULL, 51, 5, 'Online Banking', 'Delivery', 0, 0, '2022-02-08 12:40:00', 'No.10, Jalan Durian, Taman Hang Jaya'),
(800011, 'F0004', 300005, NULL, 37.5, 3, 'Cash', 'Pick Up', 0, 0, '2022-02-08 12:45:00', 'NULL'),
(800012, 'F0010', 300003, NULL, 62.5, 5, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-05-08 13:15:00', 'NULL'),
(800013, 'F0014', 300022, NULL, 61.2, 4, 'Cash', 'Pick Up', 0, 0, '2022-07-08 13:35:00', 'NULL'),
(800014, 'F0015', 300011, NULL, 15.3, 1, 'Tng Ewallet', 'Delivery', 0, 0, '2022-08-08 13:40:00', 'No.11, Jalan Cemerlang'),
(800015, 'F0003', 300002, NULL, 51, 5, 'Online Banking', 'Delivery', 0, 0, '2022-12-08 12:20:50', 'No.22, Jalan Seri Gemilang, Melaka'),
(800016, 'F0020', 300008, 'Extra sauce', 30.6, 2, 'Cash', 'Pick Up', 0, 0, '2022-10-08 23:05:00', 'NULL'),
(800017, 'F0011', 300020, 'No onion', 22.6, 2, 'Cash', 'Delivery', 0, 0, '2022-06-08 13:20:00', 'No.12, Jalan Bunga Raya, Malacca'),
(800018, 'F0012', 300011, 'Spicy level 3', 37.5, 3, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-06-08 13:25:02', 'NULL'),
(800019, 'F0013', 300010, NULL, 32.6, 2, 'Online Banking', 'Delivery', 0, 0, '2022-07-08 13:30:00', 'No.22, Jalan Seri Gemilang, Melaka'),
(800020, 'F0005', 300026, NULL, 32.6, 2, 'Tng Ewallet', 'Delivery', 0, 0, '2023-01-08 14:30:00', 'No.11, Jalan Cemerlang'),
(800021, 'F0006', 300007, NULL, 15.3, 1, 'Cash', 'Pick Up', 0, 0, '2023-01-08 17:35:00', 'No.7, Jalan Bunga Raya'),
(800022, 'F0019', 300012, NULL, 52, 4, 'Tng Ewallet', 'Delivery', 0, 0, '2022-10-08 14:00:45', 'No.5, Jalan Harmoni, Melaka'),
(800023, 'F0020', 300015, 'Extra sauce', 30.6, 2, 'Cash', 'Pick Up', 0, 0, '2022-10-08 23:05:00', 'NULL'),
(800024, 'F0011', 300010, 'No onion', 22.6, 2, 'Cash', 'Delivery', 0, 0, '2022-06-08 13:20:00', 'No.12, Jalan Bunga Raya, Malacca'),
(800025, 'F0004', 300004, 'Extra cheese', 37.5, 3, 'Cash', 'Pick Up', 0, 0, '2022-12-08 14:25:34', 'NULL'),
(800026, 'F0020', 300017, 'Extra sauce', 30.6, 2, 'Cash', 'Pick Up', 0, 0, '2022-10-08 23:05:00', 'NULL'),
(800027, 'F0011', 300011, 'No onion', 22.6, 2, 'Cash', 'Delivery', 0, 0, '2022-06-08 13:20:00', 'No.12, Jalan Bunga Raya, Malacca'),
(800028, 'F0012', 300029, 'Spicy level 3', 37.5, 3, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-06-08 13:25:02', 'NULL'),
(800029, 'F0013', 300020, NULL, 32.6, 2, 'Online Banking', 'Delivery', 0, 0, '2022-07-08 13:30:00', 'No.22, Jalan Seri Gemilang, Melaka'),
(800030, 'F0005', 300005, 'No chili', 32.6, 2, 'Tng Ewallet', 'Delivery', 0, 0, '2022-03-08 12:50:00', 'No.15, Jalan Bukit Beruang, Melaka'),
(800031, 'F0006', 300005, NULL, 15.3, 1, 'Cash', 'Pick Up', 0, 0, '2022-03-08 12:55:00', 'NULL'),
(800032, 'F0007', 300023, NULL, 52, 4, 'Tng Ewallet', 'Delivery', 0, 0, '2022-04-08 13:00:00', 'No.15, Jalan Merdeka, Melaka'),
(800033, 'F0008', 300009, 'Extra cheese', 30.6, 2, 'Online Banking', 'Pick Up', 0, 0, '2022-04-08 13:05:00', 'NULL'),
(800034, 'F0016', 300012, 'Less salt', 10.3, 1, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-08-08 13:45:00', 'NULL'),
(800035, 'F0017', 300011, 'No MSG', 27, 2, 'Online Banking', 'Delivery', 0, 0, '2022-09-08 13:50:00', 'No.15, Jalan Merdeka, Melaka'),
(800036, 'F0001', 300021, NULL, 32, 3, 'Tng Ewallet', 'Delivery', 0, 0, '2022-11-08 14:10:00', 'No.7, Jalan Bunga Raya, Melaka'),
(800037, 'F0002', 300007, NULL, 14.99, 1, 'Cash', 'Pick Up', 0, 0, '2023-11-08 19:15:00', 'NULL'),
(800038, 'F0009', 300002, NULL, 17.3, 1, 'Cash', 'Delivery', 0, 0, '2023-05-08 13:10:00', 'No.5, Jalan Harmoni, Melaka'),
(800039, 'F0018', 300016, NULL, 9.8, 1, 'Cash', 'Pick Up', 0, 0, '2023-09-08 13:55:00', 'NULL'),
(800040, 'F0019', 300022, NULL, 52, 4, 'Tng Ewallet', 'Delivery', 0, 0, '2023-10-08 14:00:45', 'No.5, Jalan Harmoni, Melaka'),
(800041, 'F0020', 300021, 'Extra sauce', 30.6, 2, 'Cash', 'Pick Up', 0, 0, '2023-10-08 23:05:00', 'NULL'),
(800042, 'F0011', 300021, 'No onion', 22.6, 2, 'Cash', 'Delivery', 0, 0, '2023-06-08 13:20:00', 'No.12, Jalan Bunga Raya, Malacca'),
(800043, 'F0012', 300021, 'Spicy level 3', 37.5, 3, 'Tng Ewallet', 'Pick Up', 0, 0, '2022-06-08 13:25:02', 'NULL'),
(800044, 'F0013', 300020, NULL, 32.6, 2, 'Online Banking', 'Delivery', 0, 0, '2023-07-08 13:30:00', 'No.22, Jalan Seri Gemilang, Melaka'),
(800046, 'F0006', 300027, NULL, 15.3, 1, 'Cash', 'Pick Up', 0, 0, '2024-01-08 17:35:00', 'No.7, Jalan Bunga Raya'),
(800047, 'F0020', 300017, '', 29, 2, 'Online Banking', 'Pick Up', 0, 0, '2024-01-08 02:26:35', 'NULL'),
(800048, 'F0016', 300011, 'no spicy', 48, 4, 'Cash', 'Delivery', 0, 0, '2024-01-08 02:28:13', 'No.11, Jalan Cemerlang, Melaka'),
(800049, 'F0013', 300011, 'more garlic please', 122.4, 8, 'Tng Ewallet', 'Pick Up', 0, 0, '2024-01-08 02:29:09', 'NULL'),
(800050, 'F0006', 300010, 'no', 66.95, 5, 'Tng Ewallet', 'Delivery', 0, 0, '2024-01-08 02:32:28', 'No.5, Jalan Harmoni, Melaka'),
(800051, 'F0013', 300001, 'add more garlic', 47.900000000000006, 3, 'Tng Ewallet', 'Delivery', 0, 0, '2024-01-08 15:55:19', 'No.19, Jalan Gemilang, Melaka'),
(800052, 'F0014', 300024, 'no', 21.8, 2, 'Cash', 'Delivery', 0, 0, '2022-06-24 08:16:42', 'No. 13, Jalan Kang Zhuang, Melaka\r\n'),
(800053, 'F0016', 300002, 'more rice', 21.849999999999998, 2, 'Tng Ewallet', 'Pick Up', 900023, 0.05, '2024-01-09 09:49:45', 'NULL'),
(800054, 'F0016', 300003, 'no', 10.924999999999999, 1, 'Online Banking', 'Pick Up', 900022, 0.05, '2024-01-14 18:20:05', 'NULL'),
(800055, 'F0014', 300030, '', 9.9, 1, 'Tng Ewallet', 'Pick Up', 0, 0, '2024-01-14 22:43:38', 'NULL'),
(800056, 'F0005', 300005, 'no', 24.443749999999998, 3, 'Online Banking', 'Delivery', 900026, 0.05, '2024-01-15 00:12:32', 'No.10, Jalan Beruang'),
(800057, 'F0016', 300031, 'no', 64.1, 6, 'Tng Ewallet', 'Delivery', 0, 0.1, '2024-01-15 00:25:20', 'No.10, Jalan Bahagia, Yuji'),
(800058, 'F0017', 300031, 'more soup', 57.24, 4, 'Cash', 'Pick Up', 0, 0.1, '2024-01-15 00:29:00', 'NULL'),
(800059, 'F0009', 300031, 'no', 75.1716, 8, 'Tng Ewallet', 'Pick Up', 900043, 0.15000000000000002, '2024-01-15 00:31:55', 'NULL'),
(800060, 'F0020', 300005, 'no', 39.15, 3, 'Online Banking', 'Pick Up', 0, 0.1, '2024-01-15 09:48:43', 'NULL'),
(800061, 'F0020', 300005, 'more wasabi please', 29.549999999999997, 2, 'Online Banking', 'Delivery', 900042, 0.05, '2024-01-17 20:56:05', 'No.14, Jalan Utem, Melaka');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `STAFF_ID` int(11) NOT NULL,
  `SIC` varchar(30) NOT NULL,
  `SNAME` varchar(100) NOT NULL,
  `SPHONE_NO` varchar(30) NOT NULL,
  `SEMAIL` varchar(100) NOT NULL,
  `SROLE` varchar(30) NOT NULL DEFAULT 'STAFF'
) ;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`STAFF_ID`, `SIC`, `SNAME`, `SPHONE_NO`, `SEMAIL`, `SROLE`) VALUES
(50001, '811013-05-0310', 'Joanne Yan Tong En', '012-039 8392', 'joanneyan@gmail.com', 'ADMIN'),
(50002, '990920-07-9386', 'Lam Wen Yii', '012-304 2934', 'wy@gmail.com', 'ADMIN'),
(50005, '030210-02-4053', 'Gary Chong', '014-679 0123', 'gary@gmailc.om', 'STAFF'),
(50006, '981012-10-2032', 'Jenny', '012-102 3943', 'jenny@gmail.com', 'STAFF'),
(50007, '870910-02-1023', 'Ahmed', '012-102 4839', 'ahmed@gmail.com', 'STAFF');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `account`
--
ALTER TABLE `account`
  ADD PRIMARY KEY (`ACCOUNT_ID`),
  ADD KEY `ACCOUNT_CUSTOMER_FK` (`CUST_ID`),
  ADD KEY `ACCOUNT_STAFF_FK` (`STAFF_ID`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`CUST_ID`),
  ADD UNIQUE KEY `CIC` (`CIC`);

--
-- Indexes for table `feedback`
--
ALTER TABLE `feedback`
  ADD PRIMARY KEY (`FEEDBACK_ID`),
  ADD KEY `FEEDBACK_ORDERLIST_FK` (`ORDER_ID`),
  ADD KEY `FEEDBACK_CUSTOMERS_FK` (`CUST_ID`);

--
-- Indexes for table `menu`
--
ALTER TABLE `menu`
  ADD PRIMARY KEY (`MENU_ID`);

--
-- Indexes for table `orderlist`
--
ALTER TABLE `orderlist`
  ADD PRIMARY KEY (`ORDER_ID`),
  ADD KEY `ORDERLIST_MENU_FK` (`MENU_ID`),
  ADD KEY `ORDERLIST_CUSTOMER_FK` (`CUST_ID`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`STAFF_ID`),
  ADD UNIQUE KEY `SIC` (`SIC`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `account`
--
ALTER TABLE `account`
  MODIFY `ACCOUNT_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=100061;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `CUST_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=300033;

--
-- AUTO_INCREMENT for table `feedback`
--
ALTER TABLE `feedback`
  MODIFY `FEEDBACK_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=900044;

--
-- AUTO_INCREMENT for table `orderlist`
--
ALTER TABLE `orderlist`
  MODIFY `ORDER_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=800062;

--
-- AUTO_INCREMENT for table `staff`
--
ALTER TABLE `staff`
  MODIFY `STAFF_ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `account`
--
ALTER TABLE `account`
  ADD CONSTRAINT `ACCOUNT_CUSTOMER_FK` FOREIGN KEY (`CUST_ID`) REFERENCES `customer` (`CUST_ID`),
  ADD CONSTRAINT `ACCOUNT_STAFF_FK` FOREIGN KEY (`STAFF_ID`) REFERENCES `staff` (`STAFF_ID`);

--
-- Constraints for table `feedback`
--
ALTER TABLE `feedback`
  ADD CONSTRAINT `FEEDBACK_CUSTOMERS_FK` FOREIGN KEY (`CUST_ID`) REFERENCES `customer` (`CUST_ID`),
  ADD CONSTRAINT `FEEDBACK_ORDERLIST_FK` FOREIGN KEY (`ORDER_ID`) REFERENCES `orderlist` (`ORDER_ID`);

--
-- Constraints for table `orderlist`
--
ALTER TABLE `orderlist`
  ADD CONSTRAINT `ORDERLIST_CUSTOMER_FK` FOREIGN KEY (`CUST_ID`) REFERENCES `customer` (`CUST_ID`),
  ADD CONSTRAINT `ORDERLIST_MENU_FK` FOREIGN KEY (`MENU_ID`) REFERENCES `menu` (`MENU_ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
