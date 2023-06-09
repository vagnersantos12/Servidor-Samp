-- phpMyAdmin SQL Dump
-- version 3.2.4
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tempo de Gera��o: Mai 03, 2011 as 09:32 
-- Vers�o do Servidor: 5.1.41
-- Vers�o do PHP: 5.3.1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Banco de Dados: `sa-mp`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `interiorinfo`
--

CREATE TABLE IF NOT EXISTS `interiorinfo` (
  `ID` int(10) NOT NULL,
  `X` double NOT NULL DEFAULT '0',
  `Y` double NOT NULL DEFAULT '0',
  `Z` double NOT NULL DEFAULT '0',
  `INT` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `interiorinfo`
--

INSERT INTO `interiorinfo` (`ID`, `X`, `Y`, `Z`, `INT`) VALUES
(2, 2233.7554, -1114.8263, 1050.8828, 5),
(1, 267.3324, 304.8912, 999.1484, 2),
(0, 1.359, -3.1545, 999.4284, 2),
(3, 446.6046, 507.2415, 1001.4195, 12),
(4, 2217.7061, -1076.2461, 1050.4844, 1),
(5, 244.4317, 304.9705, 999.1484, 1),
(6, 1421.812, 2536.4036, 10, 10),
(7, 2260.1545, -1135.9198, 1050.6328, 10),
(8, 223.1374, 1287.6732, 1082.1406, 1),
(9, 221.8473, 1140.9165, 1082.6094, 4),
(10, 2524.7212, -1679.3707, 1015.4986, 1),
(11, 2495.9229, -1692.4541, 1014.7422, 3),
(12, 2351.9856, -1180.9213, 1027.9766, 5),
(13, 226.0194, 1239.9971, 1082.1406, 2),
(14, 260.9518, 1285.0144, 1080.2578, 4),
(15, -68.8793, 1351.9952, 1080.2109, 6),
(16, -42.6055, 1406.0785, 1084.4297, 8),
(17, 260.6821, 1237.658, 1084.2578, 9),
(18, 2317.8472, -1026.2228, 1050.2178, 9),
(19, 2237.4844, -1080.9426, 1049.0234, 2),
(20, 2365.312, -1134.897, 1050.875, 8),
(21, 2468.3335, -1698.2402, 1013.5078, 2),
(22, 235.1822, 1187.7216, 1080.2578, 3),
(23, 226.9284, 1114.3215, 1080.9962, 5),
(24, 295.1416, 1473.3671, 1080.2578, 15),
(25, 446.9616, 1397.9464, 1084.3047, 2),
(26, 23.8985, 1340.8977, 1084.375, 10),
(27, 2324.3708, -1148.6685, 1050.7101, 12),
(28, -261.0554, 1456.7123, 1084.3672, 4),
(29, 22.7388, 1404.1062, 1084.4297, 5),
(30, 140.373, 1366.9344, 1083.8594, 5),
(31, 234.1762, 1064.3101, 1084.2114, 6),
(32, -283.7711, 1471.0265, 1084.375, 15),
(33, 83.0838, 1322.9294, 1083.8662, 9),
(34, 1261.7682, -785.47, 1091.9063, 5);

-- --------------------------------------------------------

--
-- Estrutura da tabela `propertyinfo`
--

CREATE TABLE IF NOT EXISTS `propertyinfo` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `E_X` double NOT NULL,
  `E_Y` double NOT NULL,
  `E_Z` double NOT NULL,
  `E_INT` int(11) NOT NULL,
  `E_VW` int(11) NOT NULL,
  `I_X` double NOT NULL,
  `I_Y` double NOT NULL,
  `I_Z` double NOT NULL,
  `I_INT` int(11) NOT NULL,
  `TYPE` int(11) NOT NULL,
  `LEVEL` int(11) NOT NULL,
  `CASHBOX` int(11) NOT NULL,
  `NAME` varchar(30) NOT NULL,
  `OWNER` varchar(20) NOT NULL,
  `CO_OWNER` varchar(20) NOT NULL,
  `SOLD` int(11) NOT NULL,
  `LOCK` int(11) NOT NULL,
  `ALARM` int(11) NOT NULL,
  `PRICE` int(11) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;

--
-- Extraindo dados da tabela `propertyinfo`
--

INSERT INTO `propertyinfo` (`ID`, `E_X`, `E_Y`, `E_Z`, `E_INT`, `E_VW`, `I_X`, `I_Y`, `I_Z`, `I_INT`, `TYPE`, `LEVEL`, `CASHBOX`, `NAME`, `OWNER`, `CO_OWNER`, `SOLD`, `LOCK`, `ALARM`, `PRICE`) VALUES
(1, 2016.544067, -1641.657714, 14.112874, 0, 0, 223.137405, 1287.673217, 1082.140625, 1, 0, 6, 0, 'Sexy House', 'None', 'None', 0, 3, 0, 50000),
(2, 2013.571411, -1656.489501, 14.136316, 0, 0, 221.847305, 1140.916503, 1082.609375, 4, 0, 6, 0, 'None', 'Jim_Dylan', 'None', 1, 3, 0, 50000),
(3, 1498.301391, -1580.520874, 13.549818, 0, 0, 446.961608, 1397.946411, 1084.304687, 2, 2, 10, 0, 'None', 'None', 'None', 0, 0, 0, 500000);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;