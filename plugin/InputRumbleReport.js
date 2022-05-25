"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
Object.defineProperty(exports, "__esModule", { value: true });

const ModLoaderAPIInjector = require("modloader64_api/ModLoaderAPIInjector");
const PluginLifecycle = require("modloader64_api/PluginLifecycle");
const EmuAddon = require('@emulator/ml64_emu_addon.node');
// const AudioAddon = require('@sound/sfml_audio');

const path = require('path'), fs = require('fs');
const fs_extra_1 = __importDefault(require("fs-extra"));

class InputRumbleReport {
    preinit() {
        this.removeSync = fs_extra_1.default.removeSync;
        fs_extra_1.default.removeSync = function(path) {
            if (path === this.modDirName) this.deinit();
            this.removeSync(path);
        }.bind(this);

        this.modDir = __dirname;
        this.pluginTmpDir = path.join(process.cwd(), '.irrtmp');
        this.tmpModName = path.basename(path.resolve(path.join(__dirname, '..')));
        this.targetDll = path.join(process.cwd(), 'emulator', 'mupen64plus-input-sdl.dll');

        if (!fs.existsSync(this.pluginTmpDir)) fs.mkdirSync(this.pluginTmpDir);
        fs.copyFileSync(path.join(this.modDir, 'helper.node'), path.join(this.pluginTmpDir, 'helper.node'));

        this.helper = require(path.join(this.pluginTmpDir, 'helper.node'));

        this.soundPath = path.join(__dirname, 'stone_of_agony.ogg');
        if (fs.existsSync(path.join(this.pluginTmpDir, 'stone_of_agony.ogg')))
            this.soundPath = path.join(this.pluginTmpDir, 'stone_of_agony.ogg');
        this.iconPath = path.join(__dirname, 'stone_of_agony.png');
        if (fs.existsSync(path.join(this.pluginTmpDir, 'stone_of_agony.png')))
            this.iconPath = path.join(this.pluginTmpDir, 'stone_of_agony.png');

        this.initErrorCode = this.helper.initialize(this.targetDll, this.soundPath);
        this.rumbling = false;
        this.ticks = 0;
        this.iconTexture = undefined;
    }
    init() {}
    postinit() {}
    deinit() {
        this.helper.deinitialize();
    }
    onTick() {}
    onViUpdate() {
        const g = this.ModLoader.ImGui;

        if (this.initErrorCode != 0) {
            g.textColored('InputReportPlugin initialization failed', { x: 1, y: 0, z: 0, w: 1 });
            if (this.initErrorCode == -1) g.textColored('failed to open input plugin module', { x: 1, y: 0, z: 0, w: 1 });
            else if (this.initErrorCode == -2) g.textColored('failed to get report procedure', { x: 1, y: 0, z: 0, w: 1 });
            else g.text('unknown error');
            return;
        }

        if (g.beginMainMenuBar()) {
            if (g.beginMenu('Mods')) {
                if (g.beginMenu('InputRumbleReport')) {
                    this.volume = [this.helper.getVolume()];
                    if (g.sliderInt('Volume', this.volume, 0, 100, '%d%%')) {
                        this.helper.setVolume(this.volume[0]);
                    }
                    g.endMenu();
                }
                g.endMenu();
            }
            g.endMainMenuBar();
        }

        if (this.iconTexture == undefined) {
            this.iconTexture = new EmuAddon.Gfx.Texture();
            this.iconTexture.loadFromFile(this.iconPath);
        }

        if (!this.rumbling && this.helper.isRumbling()) { 
            this.rumbling = true;
            this.ticks = this.helper.getTicks();
            this.helper.playSound();
        }
        if (this.rumbling && !this.helper.isRumbling() && this.helper.getTicks() > this.ticks + 500) {
            this.rumbling = false;
        }

        if (this.rumbling) {
            let dl = g.getBackgroundDrawList();
            EmuAddon.Gfx.addSprite(dl, this.iconTexture, 
                { x: 0, y: 0, z: 42, w: 42 },
                { x: 5 + Math.random() * 2, y: 5 + Math.random() * 2, z: 42, w: 42 },
                { x: 1, y: 1, z: 1, w: 1 }, 0);
        }

        // g.setCursorPos({ x: g.getWindowSize().x - 146, y: g.getWindowSize().y - 30 });
        // g.textColored("InputRumbleReport", { x: 0.8, y: 0.8, z: 0.5, w: 1 });
    }
}

__decorate([ModLoaderAPIInjector.ModLoaderAPIInject()], InputRumbleReport.prototype, "ModLoader", void 0);
__decorate([PluginLifecycle.Init()], InputRumbleReport.prototype, "init", null);
__decorate([PluginLifecycle.onTick()], InputRumbleReport.prototype, "onTick", null);
__decorate([PluginLifecycle.onViUpdate()], InputRumbleReport.prototype, "onViUpdate", null);
module.exports = InputRumbleReport;
