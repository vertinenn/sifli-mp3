# 基于黄山派的智能音乐播放器

## 项目简介

本项目是基于思澈SDK音乐播放器示例重新实现并扩展的智能音乐播放器，集成了音乐播放、时间管理、天气查询和蓝牙连接等多项功能。采用EEZ Studio进行UI界面设计，支持触摸屏操作和物理按键控制。

## 🎵 核心功能

### 音乐播放功能
- **完整播放控制**：播放、暂停、上一首、下一首
- **进度控制**：支持进度条拖拽跳转
- **播放模式**：单曲循环、列表循环、随机播放
- **音乐列表**：支持音乐列表浏览和切换
- **歌词显示**：支持LRC格式歌词同步显示
- **物理按键**：key1单击上一首，key2长按播放/暂停，key2单击下一首

### 时间管理功能
- **实时时钟**：显示当前日期和时间
- **时间同步**：支持网络时间同步
- **时间设置**：可手动调整时间（年、月、日、时、分、秒）
- **RTC支持**：硬件实时时钟支持

### 天气查询功能 ⭐ **新增**
- **实时天气**：通过蓝牙PAN连接获取实时天气信息
- **多城市支持**：支持不同城市的天气查询
- **天气显示**：显示城市名称、天气状况、温度信息
- **自动更新**：获取天气数据后自动更新UI显示
- **网络状态检测**：自动检测网络连接状态

### 蓝牙连接功能 ⭐ **新增**
- **蓝牙PAN**：支持蓝牙个人区域网络连接
- **自动重连**：智能重连机制，防止连接中断
- **连接管理**：支持设备配对和连接管理
- **网络共享**：通过蓝牙共享手机网络连接

## 🛠️ 技术架构

### 系统架构
- **操作系统**：RT-Thread实时操作系统
- **图形界面**：LVGL v8图形库
- **音频处理**：思澈SDK音频子系统
- **网络协议**：lwIP网络协议栈
- **蓝牙协议**：BTS2蓝牙协议栈

### 线程设计
- **LVGL线程**：高优先级，负责UI渲染和交互
- **音乐播放线程**：中优先级，负责音频解码和播放
- **蓝牙PAN线程**：负责蓝牙连接和网络管理
- **主线程**：系统初始化和资源管理

### 内存管理
- **动态内存**：使用RT-Thread内存管理
- **内存清理**：定期清理机制防止内存泄漏
- **线程安全**：使用互斥锁保护共享资源

## 📁 项目结构

```
sifi_mp3_player-master/
├── Code/mp3_sd_player/          # 主项目代码
│   ├── src/                     # 源代码目录
│   │   ├── main.c              # 主程序入口
│   │   ├── bt_pan/             # 蓝牙PAN功能
│   │   │   ├── bt_pan.c        # 蓝牙连接管理
│   │   │   ├── bt_pan.h        # 蓝牙头文件
│   │   │   ├── weather.c       # 天气查询功能
│   │   │   └── weather.h       # 天气头文件
│   │   ├── fonts/              # 字体文件
│   │   └── images/             # 图片资源
│   └── project/                # 项目配置
├── UI/music_palyer/            # UI设计文件
└── README.md                   # 项目说明文档
```

## 🚀 快速开始

### 环境要求
- 立创黄山派开发板 (SF32LB52)
- SD卡 (用于存储音乐文件)
- 支持蓝牙的手机 (用于网络连接)

### 编译步骤

1. **克隆项目**
```bash
git clone https://gitee.com/ren2004/sifi_mp3_player.git
cd sifi_mp3_player
```

2. **编译项目**
```bash
cd Code/mp3_sd_player/project
scons --board=sf32lb52-lchspi-ulp -j8
```

3. **烧录固件**
```bash
build_sf32lb52-lchspi-ulp_hcpu\uart_download.bat
# 按提示选择串口，例如：please input the serial port num:10
```

### 使用说明

#### 音乐播放
1. 在SD卡中创建`music`文件夹，放入MP3文件
2. 在SD卡中创建`music_txt`文件夹，放入对应的LRC歌词文件
3. 启动设备后，点击音乐按钮进入播放界面
4. 使用触摸屏或物理按键控制播放

#### 天气查询 ⭐ **新功能**
1. 确保手机蓝牙已开启
2. 在设备上连接蓝牙PAN网络
3. 在终端输入`weather_cmd`获取天气信息
4. 点击天气按钮查看天气详情

#### 时间设置
1. 点击时间按钮进入时间界面
2. 点击设置按钮进入时间设置
3. 使用+/-按钮调整时间参数
4. 点击>按钮切换设置项目

## 🔧 配置说明

### proj.conf配置
项目使用完整的LVGL和音频配置，主要配置项包括：

```shell
# 音频配置
CONFIG_AUDIO=y
CONFIG_AUDIO_LOCAL_MUSIC=y

# LVGL配置
CONFIG_PKG_USING_LITTLEVGL2RTT=y
CONFIG_LV_USE_PERF_MONITOR=y

# 蓝牙配置
CONFIG_BT=y
CONFIG_BT_PAN=y

# 网络配置
CONFIG_LWIP=y
CONFIG_LWIP_DNS=y
```

## 📊 功能特性对比

| 功能模块 | 基础版本 | 当前版本 | 说明 |
|---------|---------|---------|------|
| 音乐播放 | ✅ | ✅ | 完整播放控制 |
| 歌词显示 | ✅ | ✅ | LRC格式支持 |
| 时间显示 | ❌ | ✅ | 实时时钟显示 |
| 时间设置 | ❌ | ✅ | 手动时间调整 |
| 天气查询 | ❌ | ✅ | 实时天气信息 |
| 蓝牙连接 | ❌ | ✅ | PAN网络连接 |
| 自动更新 | ❌ | ✅ | UI自动刷新 |

## 🐛 已知问题

1. **中文文件名乱码**：FATFS设置为936编码，读取中文文件名可能出现乱码
   - 原因：Windows系统默认使用GBK/OEM编码，嵌入式系统需要UTF-8编码
   - 解决方案：建议使用英文文件名或UTF-8编码

2. **蓝牙连接稳定性**：长时间使用可能出现连接中断
   - 已实现：自动重连机制和定期清理功能
   - 建议：定期重启设备或重新连接蓝牙

## 🔄 版本更新日志

### v2.0.0 (2025-01-27) ⭐ **重大更新**
- ✅ 新增天气查询功能
- ✅ 新增蓝牙PAN连接支持
- ✅ 新增时间管理和设置功能
- ✅ 优化UI界面和用户体验
- ✅ 改进内存管理和系统稳定性
- ✅ 添加自动UI更新机制

### v1.0.0 (基础版本)
- ✅ 基础音乐播放功能
- ✅ 歌词显示支持
- ✅ 物理按键控制
- ✅ 播放模式切换

## 🤝 贡献指南

欢迎提交Issue和Pull Request来改进项目！

1. Fork本项目
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开Pull Request

## 📄 许可证

本项目基于Apache-2.0许可证开源。

## 🔗 参考链接

- [立创·黄山派技术文档](https://wiki.lckfb.com/zh-hans/hspi-sf32lb52/lckfb-hspi-sf32lb52/)
- [SiFli-SDK官方仓库](https://gitee.com/SiFli/sifli-sdk)
- [LVGL V8官方示例](https://gitee.com/SiFli/sifli-sdk/tree/main/example/multimedia/lvgl/lvgl_v8_examples)
- [官方音乐播放器示例](https://gitee.com/SiFli/sifli-sdk/tree/main/example/multimedia/audio/mp3_sd_player)

## 📞 联系方式

如有问题或建议，请通过以下方式联系：
- 项目Issues：[GitHub Issues](https://gitee.com/ren2004/sifi_mp3_player/issues)
- 邮箱：请通过项目Issues联系

---

**项目状态**: 🟢 活跃开发中  
**最后更新**: 2025-01-27  
**版本**: v2.0.0