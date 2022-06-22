/*
Navicat MySQL Data Transfer

Source Server         : 120.79.47.22
Source Server Version : 50729
Source Host           : 120.79.47.22:6060
Source Database       : proto_ff

Target Server Type    : MYSQL
Target Server Version : 50729
File Encoding         : 65001

Date: 2021-02-27 20:29:31
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `MailDesc`
-- ----------------------------
DROP TABLE IF EXISTS `MailDesc`;
CREATE TABLE `MailDesc` (
  `id` int(11) NOT NULL,
  `title` varchar(64) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `content` varchar(512) DEFAULT NULL,
  `send_name` varchar(32) DEFAULT NULL,
  `start_time_str` varchar(32) DEFAULT NULL,
  `end_time_str` varchar(32) DEFAULT NULL,
  `add_gold` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of MailDesc
-- ----------------------------
INSERT INTO `MailDesc` VALUES ('1', '你好玩家', '1', '亲爱的玩家，欢迎进入游戏！', '系统', '2020-10-01 00:00:00', '2021-10-01 00:00:00', '0');
INSERT INTO `MailDesc` VALUES ('2', '你好玩家', '1', '测试邮件，完美登陆一次，就会发一个', '系统', '', '', '0');
INSERT INTO `MailDesc` VALUES ('3', '排行榜奖励', '3', '你在猎人等级排行榜上升到了{}名，系统向你颁发奖励。', '系统', '', '', '0');
INSERT INTO `MailDesc` VALUES ('4', '排行榜奖励', '3', '你在总念力排行榜上升到了{}名，系统向你颁发奖励。', '系统', '', '', '0');
INSERT INTO `MailDesc` VALUES ('5', '手机绑定成功奖励发放', '1', '尊敬的猎人：\n    感谢您成功绑定手机，请及时领取附件奖励，祝您生活愉快。', '系统', '', '', '0');
