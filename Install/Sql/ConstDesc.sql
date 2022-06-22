/*
Navicat MySQL Data Transfer

Source Server         : 120.79.47.22
Source Server Version : 50729
Source Host           : 120.79.47.22:6060
Source Database       : proto_ff

Target Server Type    : MYSQL
Target Server Version : 50729
File Encoding         : 65001

Date: 2021-02-27 20:29:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `ConstDesc`
-- ----------------------------
DROP TABLE IF EXISTS `ConstDesc`;
CREATE TABLE `ConstDesc` (
  `id` int(11) NOT NULL,
  `value` varchar(128) DEFAULT NULL,
  `type_name` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of ConstDesc
-- ----------------------------
INSERT INTO `ConstDesc` VALUES ('1', '1000000', '玩家初始赠送金币');
INSERT INTO `ConstDesc` VALUES ('2', '10000', '玩家初始头像');
INSERT INTO `ConstDesc` VALUES ('3', '8888', '玩家初始银行密码');
